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
#include "server.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; // буфер для приема сообщений от клиентов
    char mes[1024];
    //char *cur;
    Base B;

    // Создаем сокет для работы по TCP/IP 
    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Ошибка при вызове socket");
        exit(1);
    }
    // костыль из кода сергея александровича
    int on = 1;
    if (setsockopt(as, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) == -1) {
        perror("Ошибка при вызове setsockopt");
    }
    // Заполняем структуру адреса, на котором будет работать сервер
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; // любой сетевой интерфейс
    server.sin_port = htons(1234); // порт
    // сопоставляем адрес с сокетом
    if ((bind(as, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("Ошибка при вызове bind");
        exit(1);
    }

    // сокет as используется для приема соединений; 5 - длина очереди
    if ((listen(as, 5)) == -1)
    {
        perror("Ошибка при вызове listen");
        exit(1);
    }

    // цикл обработки клиентов
    while( 1 )
	{
        ms = accept(as, 0, 0); // выбираем первое соединение из очереди
        if (ms < 0)
        {
            perror("Ошибка при вызове accept");
            exit(1);
        }
        for (int i = 0; i < 1024; i++)
        {
            if (buf[i] != 0)
                std::cout << "~" << i;
        }
        bzero(buf, sizeof(buf)); // обнуляем буфер сообщения
        for (int i = 0; i < 1024; i++)
        {
            if (buf[i] != 0)
                std::cout << "~" << i;
        }
        read(ms, buf, sizeof(buf)); // читаем сообщение от клиента
        std::cout << write(ms, buf, sizeof(buf));
        std::cout << write(ms, buf, sizeof(buf));
        close(ms); // закрываем соединение с клиентом
        printf("message is = %s, Size = %d\n", buf, strlen(buf));

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) break;
        //cur = buf;
        //while (cur[0] == ' ') cur = cur + 1;

        std::istringstream in(buf);
        int er_code = B.do_from(in);
        if (er_code < 0) { std::cout << "~~~~" << er_code << "\n"; close(as); return er_code; }
    }
    close( as ); // закрываем порт 1234; клиенты больше не могут подключаться
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
