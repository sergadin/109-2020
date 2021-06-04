#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"

int main(int argc, char* argv[])
{
    int s;
    struct sockaddr_in server;
    struct hostent* hp;

    if (argc < 4) { return 1; } // должно быть 3 аргумента: адрес, порт и сообщение

    // Создаем сокет для работы по TCP/IP
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Ошибка при вызове socket");
        exit(1);
    }

    // Заполняем струтуру с адресом сервера
    server.sin_family = AF_INET; // протокол IP
    hp = gethostbyname(argv[1]); // Обращаемся к DNS и узнаем адрес по символьному имени
    bcopy(hp->h_addr, &server.sin_addr, hp->h_length); // копируем из hp->h_addr в &server.sin_addr hp->h_length байт
    server.sin_port = htons(atoi(argv[2])); // номер порта, на котором запущен сервер

    // устанавливаем соединение с сервером
    if ((connect(s, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("Ошибка при вызове connect");
        exit(1);
    }

    write(s, argv[3], strlen(argv[3])); // посылаем строчку

    char buf[1024];
    bzero(buf, sizeof(buf));
    read(s, buf, sizeof(buf));
    std::cout << "Recieved message: " << buf << "\n";
    bzero(buf, sizeof(buf));
    read(s, buf, sizeof(buf));
    std::cout << "Recieved message: " << buf << "\n";

    for (int iii = 0; iii < 100; iii++)
    {
        bzero(buf, sizeof(buf));
        read(s, buf, sizeof(buf));
        std::cout << "  Command: " << buf << "\n";

        if (strcmp(buf, "END") == 0)
        {
            std::cout << "End of message processing\n";

            break;
        }

        if (strcmp(buf, "quit") == 0)
        {
            std::cout << "End of message processing\n";
            std::cout << "The server has shut down\n";

            break;
        }
    }

    close(s);
    return 0;
}