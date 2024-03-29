
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
            printf("Send error.\n");
            break;
        }
        total += n;
    }
    return(n == -1 ? -1 : total);
}

int sendn(int s, int *buf, int len, int flags)
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
    if (sock < 0)
    {
    perror("client: socket was not created \n");
    exit (EXIT_FAILURE);
    }
    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(26565);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    if(connect(sock, (const struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        printf("Сlient: Connecting error.\n");
        exit(-1);
    }
    
    int N = 0;
    fprintf(stdout, "Сlient:Cколько строк в матрице? > ");
    fscanf(stdin, "%d", &N);
    
    int ok = sendn(sock, &N, 1, 0);
    if(ok == -1)
    {
        printf("Сlient: Send error.\n");
        exit(-1);
    }
    
    double matrix[N*N];
    for ( int i = 0; i < N*N; i++ )
    {
        matrix[i] = 0;
    }
    
    printf("Сlient: Введите матрицу \n");
    
    for ( int i = 0; i < N*N; i++ )
    {
        scanf("%lf", matrix + i );
    }
    
    
    ok = sendmatrix(sock, matrix, N*N*8, 0);
    if(ok == -1)
    {
        printf("Сlient: Send error.\n");
        exit(-1);
    }
    
    printf("Client: Если хотите умножить матрицу на число нажмите 1 ,если хотите найти максимум в строке,нажмите 2\n");
       int k = 0;
       fscanf(stdin,"%d", &k);
       ok = sendn(sock, &k, 1, 0);
       if(ok == -1)
       {
           printf("Сlient: Send error.\n");
           exit(-1);
       }

       if(k == 1)
       {
           printf("Сlient: На какое число вы хотите умножить?\n");

           int v;
          
              fscanf(stdin,"%d", &v);
           

           ok = sendn(sock, &v, 1, 0);
           if(ok == -1)
           {
               printf("Сlient: Send error.\n");
               exit(-1);
           }


           printf("Сlient:  Результат операции: \n");
           double buffer[N*N];
           recv(sock, buffer, N*N*8, 0);
           for ( int i = 0; i < N*N; i++ )
           {
               printf("%lf\n", buffer[i]);
           }
       }
       else if(k == 2)
       {
           printf("Сlient: В какой строчке найти максимум?\n");

           int p = 0;
           fscanf(stdin,"%d", &p);
           p = p - 1;

           ok = sendn(sock, &p, 1, 0);
           if(ok == -1)
           {
               printf("Сlient: Send error.\n");
               exit(-1);
           }

           double max = 0;
           ok = recv(sock, &max, 8, 0);
           if(ok == -1)
           {
               printf("Recive error.\n");
           }

          printf("\n Сlient: Сервер вернул : %f \n", max);
       }
       
   
    
   /*
    double buffer[N*N];
    recv(sock, buffer, N*N*8, 0);
    printf("\n Сlient: Server sent matrix:\n");
    
    for ( int i = 0; i < N*N; i++ )
    {
        printf("%lf\n", buffer[i]);
    } */
    
    close(sock);
    return 0;
}
