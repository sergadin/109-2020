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

#define BUFLEN 512
int N;
int sendall(int s, char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while (total < len)
    {
        n = send(s, buf+total, len - total, flags);
        if(n == -1)
        {
            printf("Send error.\n");
            break;
        }
        total += n;
    }
    return (n == -1 ? -1 : total);
}


int main(int argc, char* argv[], char* envp[])
{
    char buffer[BUFLEN];
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("Creating socket error.\n");
        exit(-1);
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        printf("Binding socket error.\n");
        exit(-1);
    }

    if(listen(sock, 1) == -1)
    {
        printf("Listening error.\n");
        exit(-1);
    }

    struct sockaddr_in client_addr;
    unsigned int client_addrlen = 0;
    while(1)
    {
        int com_socket = accept(sock,(struct sockaddr *) &client_addr, &client_addrlen);
        if(com_socket == -1)
        {
            printf("Accept error.\n");
            exit(-1);
        }
        
        int ok = recv(com_socket, buffer, 1024, 0);
        if(ok == -1)
        {
            printf("Recive error.\n");
            break;
        }
        
        int N = atoi(buffer);
        double *matrix = (double *)malloc(sizeof(double)*N*N);
        
        for ( int i = 0; i < N*N; i++ )
        {
            int ok = recv(com_socket, buffer, 1024, 0);
               if(ok == -1)
               {
                   printf("Recive error.\n");
                   break;
               }
            matrix[i] = atoi(buffer);
        }
        
         ok = recv(com_socket, buffer, 1024, 0);
        if(ok == -1)
        {
            printf("Recive error.\n");
            break;
        }
        
        int k = atoi(buffer);
        if (k==1)
           {
                ok = recv(com_socket, buffer, 1024, 0);
               if(ok == -1)
               {
                   printf("Recive error.\n");
                   break;
               }
               int p = atoi(buffer);
               for (int i = 0; i < N*N; i++ )
               {matrix[i] = matrix[i]*p;}
               
           }
        if (k==1)
        {      ok = recv(com_socket, buffer, 1024, 0);
            if(ok == -1)
            {
            printf("Recive error.\n");
            break;
            }
            int p = atoi(buffer);
            double max = matrix[p*(N)];
            for (int j = 0; j < N; j++ )
            if (matrix[p*(N)+j] > max) {max = matrix[p*(N)+j];}
            
        }
        
        
        
        for ( int i = 0; i < N*N; i++ )
        {  buffer[0] = (char)(matrix[i]);
            
          int OK = sendall(com_socket, buffer, ok, 0);
          if(OK == -1)
            {
            printf("Send error.\n");
            exit(-1);
             }
            
        }
        
        /*  while(1)
            {
                int ok = recv(com_socket, buffer, 1024, 0);
                if(ok == -1)
                {
                    printf("Recive error.\n");
                    break;
                }
                
                if(ok == 0){break;}
                int OK = sendall(com_socket, buffer, ok, 0);
                if(OK == -1)
                {
                    printf("Send error.\n");
                    exit(-1);
                }
            }
          */
        
            close(com_socket);
          
       
    }
    close(sock);
    return 0;
}
