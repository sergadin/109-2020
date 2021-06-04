int read_from_server(int fd, char* buf) {
    int nbytes = 0, len = 0, i, j = sizeof(int);
    char* p = (char*)(&len);

    for (i = 0; j > 0; i += nbytes, j -= nbytes) {
        nbytes = read(fd, p + i, j);
        if (nbytes < 0) {
            fprintf(stderr, "Client: read length error\n");
            return -1;
        }
        else if (nbytes == 0) {
            fprintf(stderr, "Client: read length truncated\n");
            return -1;
        }
    }

    for (i = 0; len > 0; i += nbytes, len -= nbytes) {
        nbytes = read(fd, buf + i, len);
        if (nbytes < 0) {
            fprintf(stderr, "Client: read error\n");
            return -1;
        }
        else if (nbytes == 0) {
            fprintf(stderr, "Client: read truncated\n");
            return -1;
        }
    }

    if (i == 0)
        fprintf(stderr, "Client: no message\n");
    else if (buf[0] == ' ' || (!strncmp(buf, "ERROR", 5)))
        printf("%s", buf);

    return -1;
}


int write_to_client(int fd, const char* buf) {
    int nbytes = 0, len = strlen(buf) + 1, i, j = sizeof(int);
    char* p = (char*)(&len);

    for (i = 0; j > 0; i += nbytes, j -= nbytes) {
        nbytes = write(fd, p + i, j);
        if (nbytes < 0) {
            printf("Server: write length error\n");
            return -1;
        }
        else if (nbytes == 0) {
        	printf("Server: write length truncated\n");
            return -1;
        }
    }

    for (i = 0; len > 0; i += nbytes, len -= nbytes) {
        nbytes = write(fd, buf + i, len);
        if (nbytes < 0) {
            printf("Server: write error\n");
            return -1;
        }
        else if (nbytes == 0) {
            printf("Server: write truncated\n");
            return -1;
        }
    }

    return 0;
}
