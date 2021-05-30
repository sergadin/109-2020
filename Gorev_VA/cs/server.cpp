#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include "database.h"

char *scan_next(char *buf, char *mes)
{
    char *cur = buf;
    bzero(mes, sizeof(mes));
    if (cur[0] == 0) return cur;
    while (cur[0] == ' ') cur = cur + 1;
    sscanf(cur, "%s", &mes);
    cur = cur + strlen(mes);
    if (cur[0] == 0) return cur;
    while (cur[0] == ' ') cur = cur + 1;
    return cur;
}

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; /* буфер для приема сообщений от клиентов */
    char mes[1024];
    char *cur;
    Base B;
    as = socket(AF_INET, SOCK_STREAM, 0 ); /* Создаем сокет для работы по TCP/IP */
    /* Заполняем структуру адреса, на котором будет работать сервер */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* любой сетевой интерфейс */
    server.sin_port = htons(1234); /* порт */

    /* сопоставляем адрес с сокетом */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* сокет as используется для приема соединений; 5 - длина очереди */

    /* цикл обработки клиентов */
    while( 1 )
	{
        ms = accept(as, 0, 0); // выбираем первое соединение из очереди 
        bzero(buf, sizeof(buf)); // обнуляем буфер сообщения 
        read(ms, buf, sizeof(buf)); // читаем сообщение от клиента
        close(ms); // закрываем соединение с клиентом
        printf("message is = %s\n", buf);

        cur = scan_next(buf, mes);
        if (strcmp(mes, "quit") == 0) break;

        while (1)
        {
            cur = scan_next(cur, mes);
            printf("mes = %s, size = %d\n", mes, strlen(mes));

            /*if (strcmp(mes, "add_detail") == 0)
                while (1)
                {
                    bzero(mes, sizeof(mes));
                    sscanf(cur, "%s", &mes);
                    if 
                    printf("mes = %s, size = %d\n", mes, strlen(mes));
                }*/

            if (cur[0] == 0) break;
        }
    }
    close( as ); /* закрываем порт 1234; клиенты больше не могут подключаться */
    return 0;
}

/*
ms = accept(as, 0, 0); // выбираем первое соединение из очереди 
bzero(buf, sizeof(buf)); // обнуляем буфер сообщения 
read(ms, buf, sizeof(buf)); // читаем сообщение от клиента 
close(ms); // закрываем соединение с клиентом
printf("message is = %s\n", buf);
if (strcmp(buf, "quit") == 0) break;
*/
