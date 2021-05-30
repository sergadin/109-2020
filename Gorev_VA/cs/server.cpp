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

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; /* буфер для приема сообщений от клиентов */
    char mes[1024];
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

        while (1)
        {
            bzero(mes, sizeof(mes));
            if (sscanf(buf, "%s", &mes) != 1)
                break;
            printf("mes = %s\n", mes);
            if (strcmp(mes, "quit") == 0) close(as);
            /*if (strcmp(mes, "add_detail") == 0)
            {

            }*/
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
