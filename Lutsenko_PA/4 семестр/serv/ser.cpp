#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include "unistd.h"

#define PORT 5555


int writeToClient (int fd,int n,  double *syst);
int readFromClient (int fd,int n,  double *syst);
int N;
//void PrintAddr (const struct sockaddr_in &addr, const char *text);

int main(void)
{
 
    int sock , i, err , new_sock, opt = 1;
    fd_set active_set, read_set;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    double *syst = (double *)malloc(sizeof(double) * N * N);
    socklen_t size;
    
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("server: socket was not created \n");
        exit (EXIT_FAILURE);
    }
    setsockopt(sock,SQL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));
    
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr =htonl(INADDR_ANY);
    err = bind (sock, (struct sockaddr*)&addr,sizeof(addr));
   
    if (err < 0)
    {
        perror("server: can not bund socket \n");
        exit (EXIT_FAILURE);
    }
    
    
    err = listen(sock,2);
    if (err < 0)
    {
       perror("server: listen queue failure \n");
        exit (EXIT_FAILURE);
    }
    
    FD_ZERO(%active_set);
    FD_SET(sock, %active_set);

    
    while (1)
    {
        
        read_set = active_set;
        if (select(FD_SETSIZE,&read_set,NULL,NULL,NULL)<0)
        {
            perror("server: select failure \n");
            exit (EXIT_FAILURE);
        }
        
        
        for (i=0;i<FD_SETSIZE;i++)
        {
            if (FD_ISSET(i,&read_set))
            {
                if(i==sock)
                {
                    size = sizeof(client);
                    new_sock = accept(sock,(struct sockaddr*)&client,&size);
                    if (new_sock<0)
                    {
                        perror("server:accept failure \n");
                        exit (EXIT_FAILURE);
                    }
                    fprintf (stdout, "Server: connect from host %s, port &hu.\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                    FD_SET (new_sock,&active_set);
                }
                else
                {
                    err = readFromClient(i,N,syst);
                    if (err<0) {close(i); FD_CLP(i,&active_set);}
                }
                    
                
            }
        }
        
     
    }
    
    
    fprintf (stdout, "the end\n");
    
    close(sock);
    exit (EXIT_SUCCESS);
    
}

int writeToClient (int fd,int n, double *syst)
{
    int ok;
    
     for ( int i = 0; i < n; i++ )
     for (int  j = 0; j < n; j++ )
          syst[i*(N)+j] = syst[i*(N)+j]*3;
        
      

    ok = write (fd, syst ,n*n);
    if (ok != 0) fprintf(stdout, "server: i sent the answer");
    
    if (ok < 0) {perror("server: writing failure");return -1;}
    return 0;
}

int readFromClient (int fd,int n, double *syst)
{
    int ok;
    N=n;
    ok = read(fd,syst,n*n);
    if (ok < 0) {perror("server:reading failure");return -1;}
    else if (ok == 0) {fprintf (stderr,"server: no data\n"); return -1;}
    else {fprintf(stdout, "server: i got the message ");}

    return 0;
}



