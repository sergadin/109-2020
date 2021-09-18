
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

int sendmatrix(int s, double *buf, int len, int flags)
{
    int total = 0;
    int n;
    
    while (total < len)
    {
        n = send(s, buf+total, len - total, flags);
        if(n == -1)
        {
            fprintf(stdout,"Send error");
            break;
        }
        total += n;
    }
    return(n == -1 ? -1 : total);
}



int main(int argc, char* argv[], char* envp[])
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("Creating socket error\n");
        exit(-1);
    }
    
    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        printf("Binding socket error\n");
        exit(-1);
    }
    
    if(listen(sock, 1) == -1)
    {
        printf("Listening error\n");
        exit(-1);
    }
    
    struct sockaddr_in client_addr;
    unsigned int client_addrlen = 0;
    while(1)
    {
        int com_socket = accept(sock,(struct sockaddr *) &client_addr, &client_addrlen);
        if(com_socket == -1)
        {
            printf("Accept error\n");
            exit(-1);
        }
        
        int N = 0;
        int ok = recv(com_socket, &N, 1, 0);
        if(ok == -1)
        {
            printf("Recive error\n");
            break;
        }
        
        double matrix[N*N];
        
        ok = recv(com_socket, matrix, N*N*8, 0);
        if(ok == -1)
        {
            printf("Recive error\n");
            break;
        }
        
        
        
        ok = sendmatrix(com_socket, matrix, N*N*8, 0);
        if(ok == -1)
        {
            printf("Send error\n");
            exit(-1);
        }
        close(com_socket);      
    }
    close(sock);
    return 0;
}
