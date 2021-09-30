#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#define PORT_THIS 5556
#define PORT_TO 5555
#define SERVER_NAME "127.0.0.1"


int sendNToServer (int fd);
int sendMatrixToServer (int fd);
int readFromServer (int fd);
int N;

int main(void)
{




int sock , i, err, opt = 1;

struct sockaddr_in addr_to; // номер порта и айпи алрес
struct sockaddr_in addr_from;
struct sockaddr_in addr_this;
struct hostent *hostinfo;

hostinfo = gethostbyname(SERVER_NAME); // получаем информацию о сервере и кго днс имени
if (hostinfo == NULL)
{
fprintf(stderr, "unknown host %s\n",SERVER_NAME);
exit (EXIT_FAILURE);
}

addr_to.sin_family = AF_INET;
addr_to.sin_port = htons(PORT_TO);
addr_to.sin_addr = *(struct in_addr*) hostinfo ->h_addr;

/*addr_this.sin_family = AF_INET;
addr_this.sin_port = htons(PORT_THIS);
addr_this.sin_addr.s_addr = INADDR_ANY; */

//sock = socket (AF_INET, SOCK_DGRAM, 0);
    sock = socket (AF_INET, SOCK_STREAM, 0);
if (sock < 0)
{
perror("client: socket was not created \n");
exit (EXIT_FAILURE);
}
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));

/*err = connect (sock, (struct sockaddr*)&addr_to,sizeof(addr_to));
if (err < 0)
{
perror("client: connect failure \n");
exit (EXIT_FAILURE);
}
fprintf (stdout, "connection is ready\n"); */
    if(connect(sock, (const struct sockaddr*)&addr_to, sizeof(struct sockaddr_in)) == -1)
    {
        printf("client: connecting error.\n");
        exit(-1);
    }

while (1)
{ if (sendNToServer(sock)<0) break;
if (sendMatrixToServer(sock)<0) break;
if (readFromServer(sock)<0) break;
}

fprintf (stdout, "the end\n");

close(sock);
exit (EXIT_SUCCESS);

}
int sendNToServer (int fd)
{

char buf[1];

fprintf(stdout, "сколько строк в матрице? > ");
fscanf(stdin, "%s", buf);
N = atoi(buf);

int ok;

ok = write (fd,buf,1);
if (ok < 0) {perror("client:sending N problem");return -1;}
else {fprintf(stdout, "client: я отправил N = %d .Введите элементы матрицы:\n",N);}
return 0;
}

int sendMatrixToServer (int fd)
{

int ok;
double *matrixbuf = (double *)malloc(sizeof(double) * N * N);


for ( int i = 0; i < N; i++ ) {
for (int j = 0; j < N; j++ )
{ fscanf(stdin, "%lf", &matrixbuf[i*(N)+j] );}}



ok = write (fd, matrixbuf,N*N);
if (ok < 0) {perror("\n client: problem with sending matrix");return -1;}
else {fprintf(stdout, "client: я отправил matrix ");}
return 0;
}

int readFromServer (int fd)
{
int ok;
double *matrix = (double *)malloc(sizeof(double)*N*N);


ok = read(fd,matrix,N*N);
if (ok < 0) {perror("read");return -1;}
else if (ok == 0) {fprintf (stderr,"client: no message\n");}
else {fprintf(stdout, "server's reply:");
for ( int i = 0; i < N; i++ )
{
for (int j = 0; j < N; j++ )
{
printf( "%.1f\t", matrix[i*(N)+j] );
}
printf( "\n");
}}


return 0;
}
