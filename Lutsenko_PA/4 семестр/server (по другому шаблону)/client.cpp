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
    return(n == -1 ? -1 : total);
}

int main(int argc, char* argv[], char* envp[])
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(26565);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (const struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        printf("Сlient: Connecting error.\n");
        exit(-1);
    }

        
        char message[BUFLEN];
        fprintf(stdout, "Сlient:Cколько строк в матрице? > ");
        fscanf(stdin, "%s", message);
        int N = atoi(message);
        char buffer[sizeof(message)];
        int ok = sendall(sock, message, sizeof(message), 0);
        if(ok == -1)
        {
            printf("Сlient: Send error.\n");
            exit(-1);
        }
     //   recv(sock, buffer, sizeof(message), 0);
     //   printf("\n Сlient: Сервер вернул : %s \n", buffer);
    
        
        char matrix[N*N][BUFLEN];
        printf("Сlient: Введите матрицу \n");
         
        for ( int i = 0; i < N*N; i++ )
        { scanf("%s", matrix[i] );}
    
        for ( int i = 0; i < N*N; i++ )
        {
            int ok = sendall(sock, matrix[i], sizeof(matrix[i]), 0);
           if(ok == -1)
          {
            printf("Сlient: Send error.\n");
            exit(-1);
          }
         
        }
    
    /*   for ( int i = 0; i < N*N; i++ )
              {
                
                recv(sock, buffer, sizeof(matrix[i]), 0);
                 printf("\n Сlient: Сервер вернул : %s \n", buffer);
              }
     */
     
        printf("Сlient: Если хотите умножить матрицу на число нажмите 1 ,если хотите найти максимум в строке,нажмите 2\n");
       fscanf(stdin, "%s", message);
        ok = sendall(sock, message, sizeof(message), 0);
        if(ok == -1)
       {
         printf("Сlient: Send error.\n");
         exit(-1);
       }
       int k = atoi(message);
       if (k==1)
       {
         printf("Сlient: На какое число вы хотите умножить?\n");
         fscanf(stdin, "%s", message);
           
            ok = sendall(sock, message, sizeof(message), 0);
                     if(ok == -1)
                    {
                      printf("Сlient: Send error.\n");
                      exit(-1);
                    }
           
           for ( int i = 0; i < N*N; i++ )
           {
             
             recv(sock, buffer, sizeof(matrix[i]), 0);
             printf("\n Сlient: Сервер вернул : %s \n", buffer);
           }
           
       }
       if (k==2)
       {
           printf("Сlient: В какой строчке найти максимум?\n");
           fscanf(stdin, "%s", message);
            ok = sendall(sock, message, sizeof(message), 0);
           if(ok == -1)
           {
             printf("Сlient: Send error.\n");
             exit(-1);
           }
            printf("Сlient:  Результат операции: \n");
       }
       
      
    
        
   
    close(sock);
    return 0;
}

//делает пересылки в байтах
