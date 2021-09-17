#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <ctype.h>
#include <arpa/inet.h>
#include "unistd.h"

#define PORT 5555


int writeToClient (int fd, double *matrixbuf);
int readMatrixFromClient (int fd, double *matrixbuf );
int readNFromClient (int fd, char *buf );
int SendMax(int n);
int N;

int main(void)
{

int sock , i, err;
int opt = 1;
struct sockaddr_in addr_from;
struct sockaddr_in addr_this;
char buf[1];
    
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
    perror("server: socket was not created \n");
    exit (EXIT_FAILURE);
    }
    else fprintf(stdout, "server: socket is ready\n");
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));

    
    addr_this.sin_family = AF_INET;
    addr_this.sin_port = htons(PORT);
    addr_this.sin_addr.s_addr = htonl(INADDR_ANY);

 /*addr_this.sin_family = AF_INET;
addr_this.sin_port = htons(PORT);
addr_this.sin_addr.s_addr =INADDR_ANY;
*/





/*err = bind (sock, (struct sockaddr*)&addr_this,sizeof(addr_this));
if (err < 0)
{
perror("server: can not bund socket \n");
exit (EXIT_FAILURE);
}
else fprintf(stdout, "server: socket is bound\n");

   */
    if(bind(sock, (struct sockaddr*) &addr_this, sizeof(addr_this)) == -1)
    {
        printf("Binding socket error.\n");
        exit(-1);
    }

    if(listen(sock, 1) == -1)
    {
        printf("Listening error.\n");
        exit(-1);
    }



fprintf(stdout, "server: connection ready/n");

while (1)
{
err = readNFromClient(sock,buf);
double *matrixbuf = (double *)malloc(sizeof(double) * N*N);
err = readMatrixFromClient(sock,matrixbuf);
    if (err<0) break;
}





fprintf (stdout, "the end\n");

close(sock);
exit (EXIT_SUCCESS);

}

int writeToClient (int fd, double *matrixbuf)
{
int ok;


ok = write (fd, &matrixbuf ,N*N);
if (ok != 0) fprintf(stdout, "server: i sent the answer");

if (ok < 0) {perror("server: writing failure");return -1;}
return 0;
}

/*int SendMax(int fd,int n, double *matrix)
{
int ok;
int max = matrix[n*(N)];
char charmax;
for (int j = 0; j < n; j++ )
if (matrix[n*(N)+j] > max) {max = matrix[n*(N)+j];}

charmax = max + '0';

ok = write (fd, charmax ,sizeof(char));
if (ok != 0) fprintf(stdout, "server: i sent max");
if (ok < 0) {perror("server: sending max failure");return -1;}
return 0;
} */

int readNFromClient (int fd, char *buf)
{
int ok;
ok = read(fd,buf,1);
N = atoi(buf);
if (ok < 0) {perror("server:reading N failure");return -1;}
else if (ok == 0) {fprintf (stderr,"server: no N\n"); return -1;}
else {fprintf(stdout, "server: i got the N ");}

return 0;
}

int readMatrixFromClient (int fd, double *matrixbuf)
{
int ok;
ok = read(fd,matrixbuf,N*N);
if (ok < 0) {perror("server:reading Matrix failure");return -1;}
else if (ok == 0) {fprintf (stderr,"server: no Matrix data\n"); return -1;}
else {fprintf(stdout, "server: i got the Matrix ");}

return 0;
}


