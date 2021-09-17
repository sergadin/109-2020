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
    char buffer[1024];
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket == -1)
    {
        printf("Creating socket error.\n");
        exit(-1);
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(tcp_socket, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        printf("Binding socket error.\n");
        exit(-1);
    }

    if(listen(tcp_socket, 1) == -1)
    {
        printf("Listening error.\n");
        exit(-1);
    }

    struct sockaddr_in client_addr;
    unsigned int client_addrlen = 0;
    while(1)
    {
        int com_socket = accept(tcp_socket,(struct sockaddr *) &client_addr, &client_addrlen);
        if(com_socket == -1)
        {
            printf("Accept error.\n");
            exit(-1);
        }

        
            while(1)
            {
                int bytes_recv = recv(com_socket, buffer, 1024, 0);
                if(bytes_recv == -1)
                {
                    printf("Recive error.\n");
                    break;
                }
                if(bytes_recv == 0){break;}
                int symnum = sendall(com_socket, buffer, bytes_recv, 0);
                if(symnum == -1)
                {
                    printf("Send error.\n");
                    exit(-1);
                }
            }
            close(com_socket);
          
       
    }
    close(tcp_socket);
    return 0;
}
