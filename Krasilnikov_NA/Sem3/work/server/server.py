import os
import sys
import socket
import threading
import string
import random


BUFFER_LEN = 4096
usedfiles = set()
continue_working = True
db_locker = threading.Lock()


def receive_from_client(sock):
    res = ''
    while True:
        s = sock.recv(BUFFER_LEN).decode("utf-8")
        if s[-1] == '\0':
            res += s[:-1]
            break
        else:
            res += s
    return res

def receive_from_db(fin):
    while True:
        s = fin.readline()
        if not s.strip('\r\n'):
            break
        yield s

def send_to_client(sock, msg):
    sock.send((msg + '\0').encode("utf-8"))

def call_db(cmd, fout):
    print(cmd.strip(), file=fout, flush=True)

def send_file(filename, sock):
    try:
        fin = open(filename, 'r')
        send_to_client(sock, "".join(fin.readlines()))
        fin.close()
    except:
        send_to_client(sock, "")
        print("tmp filename error")

def getTmpFilename():
    while True:
        s = ''.join(random.choice(string.ascii_lowercase) for _ in range(8))
        if s not in usedfiles:
            return s

def listen_clients(fin, fout):
    srv_sock = socket.socket()
    srv_sock.bind((sys.argv[1], int(sys.argv[2])))
    threads = []
    client_index = 0
    print("".join(receive_from_db(fin)))
    while True:
        srv_sock.listen(1)
        client_index += 1
        client_sock, addr = srv_sock.accept()
        print("Connected client #{} ip: {} port: {}".format(client_index, *addr))
        send_to_client(client_sock, "DB start\n")
        thread = threading.Thread(target=process_client, args=(fin, fout, client_sock, client_index))
        threads.append(thread)
        thread.start()
    for t in threads:
        t.join()
    srv_sock.close()

def process_client(fin, fout, client_sock, index):
    while not client_sock._closed:
        cmd = receive_from_client(client_sock)
        if cmd.strip('\n\r\t ') == "exit":
            print("Client #{} exit".format(index))
            break
        if cmd.split()[0] == "saveAsTxtFile":
            filename = os.getcwd() + '/' + getTmpFilename()
            usedfiles.add(filename)
            db_locker.acquire()
            call_db("saveAsTxtFile " + filename, fout)
            s = ""
            while not s:
                s = fin.readline()
            receive_from_db(fin)
            db_locker.release()
            send_file(filename, client_sock)
            usedfiles.remove(filename)
            os.remove(filename)
            send_to_client(client_sock, "Saved as")
            continue
        db_locker.acquire()
        call_db(cmd, fout)
        send_to_client(client_sock, "".join(receive_from_db(fin)))
        db_locker.release()
    client_sock.close()

def init_db():
    read1, write1 = os.pipe()
    read2, write2 = os.pipe()

    if os.fork() == 0:
        os.close(read1)
        os.close(write2)
        os.dup2(read2, 0)
        os.close(read2)
        os.dup2(write1, 1)
        os.close(write1)
        os.execlp("./main", "/main")
        exit(0)

    os.close(read2)
    os.close(write1)
    fin = os.fdopen(read1, 'r')
    fout = os.fdopen(write2, 'w')
    receive_from_db(fin)
    return fin, fout


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Wrong args: Must be host and port")
        exit(-1)

    fin, fout = init_db()
    listen_clients(fin, fout)

    os.wait()
