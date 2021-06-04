import sys
import socket

BUFFER_LEN = 4096

def send_to_server(cmd, sock):
    sock.send((cmd + '\0').encode("utf-8"))

def receive_from_server(sock):
    res = ''
    while True:
        s = sock.recv(BUFFER_LEN).decode("utf-8")
        if s[-1] == '\0':
            res += s[:-1]
            break
        else:
            res += s
    return res

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Wrong args: Must be host and port")
        exit(-1)

    sock = socket.socket()
    sock.connect((sys.argv[1], int(sys.argv[2])))
    print(receive_from_server(sock))

    while not sock._closed:
        cmd = input()
        if not cmd.strip('\n\r\t '):
            continue
        if cmd == "exit":
            send_to_server(cmd, sock)
            break
        if cmd.split()[0] == 'uploadFromTxtFile':
            try:
                fin = open(cmd.split()[1], 'r')
                while True:
                    s = fin.readline()
                    if not s:
                        break
                    send_to_server(s, sock)
                    print(receive_from_server(sock), end='')
            except:
                print("Bad filename")
            continue
        elif cmd.split()[0] == 'saveAsTxtFile':
            try:
                if len(cmd.split()) != 2:
                    raise ValueError("No file")
                send_to_server(cmd, sock)
                fout = open(cmd.split()[1], 'w')
                print(receive_from_server(sock), file=fout)
                fout.close()
                print(receive_from_server(sock), cmd.split()[1])
            except:
                print("Bad filename")
            continue
        send_to_server(cmd, sock)
        print(receive_from_server(sock), end='')
    sock.close()
