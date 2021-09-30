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
#include <cctype>
#include <poll.h>
#include <string>
#include <cstring>

#define PORT   5555
#define BUFLEN   512

//int readFromClient(int fd, char *buf);
void writeToClient(int fd, char *buf, int sender);


int main(void)
{
	int sock, new_sock;
	int i, err, opt = 1;
	socklen_t size;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	char *buf;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock<0) {
		perror ("Server: socket was not created");
		exit(EXIT_FAILURE);
	}

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	if (err<0) {
		perror ("Server: cannot bind socket");
		exit(EXIT_FAILURE);
	}

	err = listen(sock, 3);
	if (err<0) {
		perror ("Server: listen queue failure");
		exit(EXIT_FAILURE);
	}

	pollfd act_set[100];
	act_set[0].fd = sock;
	act_set[0].events = POLLIN;
	act_set[0].revents = 0;
	int num_set = 1;


	while(1)
	{
		int ret = poll(act_set, num_set, -1);
		if (ret<0)
		{
			perror("Server: poll failure");
			exit(EXIT_FAILURE);
		}
		if (ret>0)
		{
			for (i = 0; i < num_set; i++)
			{
				if(act_set[i].revents & POLLIN){
					printf("Get POLLIN at fd %d, %d\n", act_set[i].fd, i);
					act_set[i].revents &=- POLLIN;
					if (i==0)
					{
						size = sizeof(client);
						new_sock = accept(act_set[i].fd, (struct sockaddr*)&client, &size);
						printf("new client at port %u\n", ntohs(client.sin_port));
						if (num_set<100)
						{
							act_set[num_set].fd = new_sock;
							act_set[num_set].events = POLLIN;
							act_set[num_set].revents = 0;
							num_set++;
						} else {
							printf("no more sockets avaliable\n");
							close(new_sock);
						}
					} else {
							int nbytes1, nbytes2, msgsize;

							nbytes1 = read(act_set[i].fd, &msgsize, 4);
							printf("msgsize = %d\n", msgsize);
							buf = new char[msgsize+1];
							nbytes2 = read(act_set[i].fd, buf, msgsize+1);

							if(nbytes2<0){
								perror("Server: read failure");
								err =  -1;
							} else if (nbytes2 == 0)
							{					
								err = -1;
							} else {
								fprintf(stdout, "Server got message: %s\n", buf);
								err = 0;
							}
						printf("%d [%s] %p\n", err, buf, strstr(buf, "stop"));
						if (err<0 || strstr(buf, "stop"))
						{	
							printf("get stop\n");
							close(act_set[i].fd);
							if (i<num_set-1)
							{
								act_set[i] = act_set[num_set-1];
								num_set--;
								i--;
							}
						} else {
							for (int k = 1; k < num_set; k++)
							{
								if (act_set[k].fd != act_set[i].fd)
								{
									writeToClient(act_set[k].fd, buf, act_set[i].fd);
								}
							}		
						}
					}
				}
			}
		}
	}
}

/*int readFromClient(int fd, char *buf){
	int nbytes1, nbytes2, msgsize;

	nbytes1 = read(fd, &msgsize, 4);
	printf("msgsize = %d\n", msgsize);
	buf = new char[msgsize];
	nbytes2 = read(fd, buf, msgsize);

	if(nbytes2<0){
		perror("Server: read failure");
		return -1;
	} else if (nbytes2 == 0)
	{
		return -1;
	} else {
		fprintf(stdout, "Server got message: %s\n", buf);
	}
	return 0;
}*/

void writeToClient(int fd, char *buf, int sender){
	int nbytes1, nbytes2;
	int msgsize;
	char whowrote[strlen(buf)+20] = {};
	sprintf(whowrote, "User#%d: ", sender-3);
	strcat(whowrote, buf);
	msgsize = strlen(whowrote)+4;
    fprintf(stdout, "New message: %s\n", whowrote);
    nbytes1 = write(fd, &msgsize, 4);
	nbytes2 = write(fd, whowrote, strlen(whowrote)+1);
	fprintf(stdout, "Write back to %d: %s\n nbytes = %d\n", fd, buf, nbytes2);

	if (nbytes2<0){
		perror("Server: write failure");
	}
}