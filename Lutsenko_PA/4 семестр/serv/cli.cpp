#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


#define SERVER_PORT 5555
#define SERVER_NAME "127.0.0.1"
#define BUFLEN 512

int writeToServer (int fd);
int readFromServer (int fd);
int N;



int main(void)
{
 
    
    

    int sock , i, err;

    struct sockaddr_in server_addr;
    struct hostent *hostinfo;

    hostinfo = gethostbyname(SERVER_NAME);
    if (hostinfo == NULL)
    {
        fprintf(stderr, "unknown host %s\n",SERVER_NAME);
        exit (EXIT_FAILURE);
    }
    
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo ->h_addr;
    
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("client: socket was not created \n");
        exit (EXIT_FAILURE);
    }
    
    
    err = connect (sock, (struct sockaddr*)&server_addr,sizeof(server_addr));
    if (err < 0)
    {
        perror("client: connect failure \n");
        exit (EXIT_FAILURE);
    }
    fprintf (stdout, "connection is ready\n");
    
    while (1)
   {
        if (writeToServer(sock)<0) break;
        if (readFromServer(sock)<0) break;
   }
    
    fprintf (stdout, "the end\n");
    
    close(sock);
    exit (EXIT_SUCCESS);
    
}

int writeToServer (int fd)
{
    int n;
  //  int m;
    
    fprintf(stdout, "сколько строк в матрице? > ");
    fscanf(stdin, "%d", &n);
    N = n;
    
//    fprintf(stdout, "сколько столбцов в матрице? > ");
  //  fscanf(stdin, "%d", &m);
    
    int ok;
    
    double *syst = (double *)malloc(sizeof(double) * n * n);
        for ( int i = 0; i < n; i++ )
        for (int  j = 0; j < n; j++ )
        fscanf(stdin, "%lf",  &syst[i*(n)+j] );
     

    ok = write (fd, syst, n*n);
    if (ok < 0) {perror("writing problem");return -1;}
    return 0;
}

int readFromServer (int fd)
{
    int ok;
    double *syst = (double *)malloc(sizeof(double) * N * N);

    
    ok = read(fd,syst,N*N);
    if (ok < 0) {perror("read");return -1;}
    else if (ok == 0) {fprintf (stderr,"client: no message\n");}
    else {fprintf(stdout, "server's reply:");
          for ( int i = 0; i < N; i++ )
            {
              for (int  j = 0; j < N; j++ )
                 {
                   printf( "%.1f\t",  syst[i*(N)+j] );
                  }
               printf( "\n");
            }}
    

    return 0;
}



