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
#include <iostream>

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

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) break;
        cur = buf;
        while (cur[0] == ' ') cur = cur + 1;

        // цикл обработки одного сообщения
        while (1)
        {
            // читаем первую команду
            bzero(mes, sizeof(mes));
            if (cur[0] == 0) break;
            while (cur[0] == ' ') cur = cur + 1;
            sscanf(cur, "%s", &mes);
            cur = cur + strlen(mes);
            while (cur[0] == ' ') cur = cur + 1;
            printf("  command = %s, size = %d\n", mes, strlen(mes));

            // добавление деталей
            if (strcmp(mes, "add_details") == 0)
                while (1)
                {
                    // читаем название детали / сообщение об окончинии добавления
                    bzero(mes, sizeof(mes));
                    if (cur[0] == 0) { close(as); return -1; }
                    while (cur[0] == ' ') cur = cur + 1;
                    sscanf(cur, "%s", &mes);
                    cur = cur + strlen(mes);
                    while (cur[0] == ' ') cur = cur + 1;
                    if (strcmp(mes, "end") == 0)
                        break;
                    else
                    {
                        printf("    new detail = %s, ", mes);
                        std::string det_name(mes);

                        if (cur[0] == 0) { close(as); return -1; }
                    
                        // читаем количество деталей
                        int det_quant;
                        if (sscanf(cur, "%d", &det_quant) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %d\n", det_quant);

                        // добавляем детали в базу
                        B.add_detail(det_name, det_quant);
                    }
                }
            
            // добавление карты
            if (strcmp(mes, "add_map") == 0)
            {
                std::vector <std::string> map;
                map.resize(1);

                // читаем название первой детали
                bzero(mes, sizeof(mes));
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%s", &mes);
                cur = cur + strlen(mes);
                while (cur[0] == ' ') cur = cur + 1;
                std::string det_name0(mes);
                map[1] = det_name0;
                std::cout << "<" << map[1] << ">";

                while (1)
                {
                    // читаем название детали / сообщение об окончинии добавления
                    bzero(mes, sizeof(mes));
                    if (cur[0] == 0) { close(as); return -1; }
                    while (cur[0] == ' ') cur = cur + 1;
                    sscanf(cur, "%s", &mes);
                    cur = cur + strlen(mes);
                    while (cur[0] == ' ') cur = cur + 1;
                    if (strcmp(mes, "end") == 0)
                        break;
                    else
                    {
                        std::string det_name1(mes);
                        map.resize(map.size() + 2);
                        map[map.size() - 2] = det_name1;
                        printf("    detail = %s, ", mes);
                        if (cur[0] == 0) { close(as); return -1; }

                        // читаем количество деталей
                        bzero(mes, sizeof(mes));
                        if (sscanf(cur, "%s", &mes) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %s\n", mes);
                        std::string det_quant1(mes);
                        map[map.size() - 1] = det_quant1;
                    }
                }

                // добавляем карту в базу
                std::cout << "<" << map[1] << ">";
                B.add_map(map);
            }

            // показать компоненты базы
            if (strcmp(mes, "show_details") == 0)
                B.show_details();
            if (strcmp(mes, "show_maps") == 0)
                B.show_maps();
            if (strcmp(mes, "show_base") == 0)
                B.show_base();

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
