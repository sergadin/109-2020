#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

#define SERVER_NAME   "127.0.0.1"
#define SERVER_PORT   5555
#define BUFLEN   512

int writeToServer (int fd);
int readFromServer (int fd);

int main(void)
{
	int sock;
	int i, err;
	struct sockaddr_in server_addr;
	struct hostent *hostinfo;
	pid_t pid;

	hostinfo = gethostbyname (SERVER_NAME);
	if (hostinfo == NULL){
		fprintf (stderr, "Unknown host\n");
		exit (EXIT_FAILURE);
	}
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock<0) {
		perror ("Client: socket was not created");
		exit(EXIT_FAILURE);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (err<0) {
		perror ("Client: cannot connect socket");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Connection ready\n");
	pid = fork();
	if (pid == -1){
		perror("fork");
        return 0;
	} else if(pid == 0){
		while(1){
			if (writeToServer(sock)<0) break;	
		}
		return 0;
	} else{
		while(1){
			if (readFromServer(sock)<0) break;
		}
		while(waitpid(-1, nullptr, WNOHANG)>0);
		fprintf(stdout, "The end\n");
		close(sock);
		exit(EXIT_SUCCESS);
	}

}


int writeToServer(int fd){
	int nbytes;
	char buf[BUFLEN];

	
	if (fgets(buf, BUFLEN, stdin)==nullptr){
		printf("error\n");
	}
	buf[strlen(buf)-1]=0;

	nbytes = write(fd, buf, strlen(buf)+1);
	if(nbytes<0){
		perror("write");
		return -1;
	}
	if(strstr(buf, "stop")) return -1;
	return 0;
}

int readFromServer(int fd){
	int nbytes;
	char buf[BUFLEN];

	nbytes = read(fd, buf, BUFLEN);

	if(nbytes<0){
		perror("read");
		return -1;
	} else if (nbytes == 0)
	{
		fprintf(stderr, "Client: no message\n");
		return -2;
	} else {
		fprintf(stdout, "%s\n", buf);
	}
	return 0;
}