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

        if (strcmp(buf, "error") == 0)
        {
            std::cout << "Error\n";

            break;
        }
        if (strcmp(buf, "add_details") == 0)
        {
            std::cout << "  Start additing details\n";
            continue;
        }
        if (strcmp(buf, "add_details_name") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "  " << buf << ") ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "Detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_details_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            for (int i = 0; i < (4 + strlen(buf)); i++)
                std::cout << " ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "Detailail's quant: " << buf << "\n";
            continue;
        }

        if (strcmp(buf, "add_map") == 0)
        {
            std::cout << "  Start additing map\n";
            continue;
        }
        if (strcmp(buf, "add_map_res") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Result detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_map_comp_name") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    " << buf << ") ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "Component detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_map_comp_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            for (int i = 0; i < (2 + strlen(buf)); i++)
                std::cout << " ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Component detailail's quant: " << buf << "\n";
            continue;
        }

        if (strcmp(buf, "can_build_map_#") == 0)
        {
            std::cout << "  Start calculating how many details can be builded by map:\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_#_num") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Number " << buf << ":\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_#_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    " << buf << " details ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << buf << "\n";
            continue;
        }
        
        if (strcmp(buf, "can_build_map") == 0)
        {
            std::cout << "  Start calculating how many details can be builded by map:\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_res") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Result detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_comp_name") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    " << buf << ") ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "Component detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_comp_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            for (int i = 0; i < (2 + strlen(buf)); i++)
                std::cout << " ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Component detailail's quant: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    " << buf << " details ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << buf << "\n";
            continue;
        }

        if (strcmp(buf, "build_map_#") == 0)
        {
            std::cout << "  Start building details by map:\n";
            continue;
        }
        if (strcmp(buf, "build_map_#_num") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Number " << buf << ":\n";
            continue;
        }
        if (strcmp(buf, "build_map_#_quant") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Want build: " << buf << " details ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << buf << "\n";
            continue;
        }
        if (strcmp(buf, "build_map_#_builded") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Builded: " << buf << " details ";

            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << buf << "\n";
            continue;
        }

        if (strcmp(buf, "read_from_file") == 0)
        {
            std::cout << "  Start reading from file:\n";
            continue;
        }
        if (strcmp(buf, "read_from_file_open") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    Filename: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "read_from_file_close") == 0)
        {
            bzero(buf, sizeof(buf));
            read(s, buf, sizeof(buf));
            std::cout << "    File: " << buf << " closed\n";
            continue;
        }
    }

    close(s);
    return 0;
}