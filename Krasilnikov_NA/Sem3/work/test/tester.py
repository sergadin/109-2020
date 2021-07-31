import os
import sys
import signal
import time
import random


def launch_client(i, port):
    fin = os.open("{}.test".format(i), os.O_RDONLY)
    fout = os.open("{}.test_res".format(i), os.O_WRONLY | os.O_CREAT)
    os.dup2(fin, 0)
    os.close(fin)
    os.dup2(fout, 1)
    os.close(fout)
    os.execlp("python3", "python3", "../client/client.py", "127.0.0.1", port)
    exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Bad args: Must be n - number of clients and test filename(file with database)")
        exit(1)

    port = str(random.randint(10000, 20000))
    os.system("make --directory=../server")

    os.chdir("../server")
    server_pid = os.fork()
    if server_pid == 0:
        os.execlp("python3", "python3", "server.py", "127.0.0.1", port)
        exit(1)
    time.sleep(5)
    os.chdir("../test")
    print("Server launched")

    if os.fork() == 0:
        launch_client(0, port)
    os.wait()
    print("DB uploaded")

    for i in range(1, int(sys.argv[1]) + 1):
        if os.fork() == 0:
            launch_client(i, port)

    for _ in range(0, int(sys.argv[1])):
        os.wait()
    os.kill(server_pid, signal.SIGKILL)
    print("Tested successfully")
