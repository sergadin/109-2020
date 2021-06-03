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
    struct sockaddr_in client;
    char buf[1024]; // буфер для приема сообщений от клиентов
    char mes[1024];
    int er_code = 0;
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
    server.sin_port = htons(1230); // порт
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
        socklen_t size;
        size = sizeof(client);
        ms = accept(as, (struct sockaddr*)&client, &size); // выбираем первое соединение из очереди
        if (ms < 0)
        {
            perror("Ошибка при вызове accept");
            exit(1);
        }
        bzero(buf, sizeof(buf)); // обнуляем буфер сообщения 
        read(ms, buf, sizeof(buf)); // читаем сообщение от клиента
        write(ms, buf, sizeof(buf));

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) { write(ms, mes, sizeof(mes)); break; }
        //cur = buf;
        //while (cur[0] == ' ') cur = cur + 1;

        std::istringstream in(buf);
        er_code = B.do_from(in, ms);
        std::cout << "er_code is " << er_code << "\n";
        if (er_code < 0)
        { 
            char cer_code[1024];
            bzero(cer_code, sizeof(cer_code));
            std::cout << "cer_code1 is " << cer_code << "\n";
            sprintf(cer_code, "%d", er_code);
            std::cout << "cer_code2 is " << cer_code << "\n";
            write(ms, cer_code, sizeof(cer_code));
            er_code = 0;
        }

        close(ms); // закрываем соединение с клиентом
    }
    close( as ); // закрываем порт 1234; клиенты больше не могут подключаться
    return er_code;
}

/*
ms = accept(as, 0, 0); // выбираем первое соединение из очереди 
bzero(buf, sizeof(buf)); // обнуляем буфер сообщения 
read(ms, buf, sizeof(buf)); // читаем сообщение от клиента 
close(ms); // закрываем соединение с клиентом
printf("message is = %s\n", buf);
if (strcmp(buf, "quit") == 0) break;
*/
