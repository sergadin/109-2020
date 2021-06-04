#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "read_write.h"

int main(int argc, char* argv[])
{
    int s, ns;
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

    char mes[1024];
    bzero(mes, sizeof(mes));
    read(s, mes, sizeof(mes));
    std::cout << "Recieved message: " << mes << "\n";
    std::cout << "Size of message: " << (int)sizeof(mes) << "\n";

    for (int iii = 0; iii < 10; iii++)
    {
        bzero(mes, sizeof(mes));
        read(s, mes, sizeof(mes));
        std::cout << mes << "\n";

        if (strcmp(mes, "END") == 0)
        {
            std::cout << "End of message processing\n";

            break;
        }

        if (strcmp(mes, "quit") == 0)
        {
            std::cout << "End of message processing\n";
            std::cout << "The server has shut down\n";

            break;
        }

        if (strcmp(mes, "error") == 0)
        {
            std::cout << "Error ";
            std::cout << "$ Size of message error: " << (int)sizeof(mes) << "\n";
            bzero(mes, sizeof(mes));
            read(s, mes, sizeof(mes));
            std::cout << "|" << mes << "|" << (int)sizeof(mes) << "|" << (int)mes[0] << "|\n";

            int er_code = 0;
            sscanf(mes, "%d", &er_code);

            std::cout << "  ";
            if ((er_code > 0) || (er_code < -16)) std::cout << "Unknown error\n";
            if (er_code == -1) std::cout << "Error in: add_details - reading name of detail\n";
            if (er_code == -2) std::cout << "Error in: add_details - reading quant of detail\n";
            if (er_code == -3) std::cout << "Error in: add_map - reading name of result detail\n";
            if (er_code == -4) std::cout << "Error in: add_map - reading name of component detail\n";
            if (er_code == -5) std::cout << "Error in: add_map - reading quant of component detail\n";
            if (er_code == -6) std::cout << "Error in: can_build_map_# - reading of number of map\n";
            if (er_code == -7) std::cout << "Error in: can_build_map_# - calculating of number of details that can be builded\n";
            if (er_code == -8) std::cout << "Error in: can_build_map - reading name of result detail\n";
            if (er_code == -9) std::cout << "Error in: can_build_map - reading name of component detail\n";
            if (er_code == -10) std::cout << "Error in: can_build_map - reading quant of component detail\n";
            if (er_code == -11) std::cout << "Error in: can_build_map - calculating of number of details that can be builded\n";
            if (er_code == -12) std::cout << "Error in: build_map_# - reading number of map\n";
            if (er_code == -13) std::cout << "Error in: build_map_# - reading number of details that must be builded\n";
            if (er_code == -14) std::cout << "Error in: build_map_# - calculating number of details that must be builded\n";
            if (er_code == -15) std::cout << "Error in: read_from_file - reading name of file\n";
            if (er_code == -16) std::cout << "Error in: read_from_file - finding file\n";

            break;
        }

        std::cout << "  Command: " << mes << "\n";


        /*if (strcmp(mes, "add_details") == 0)
        {
            std::cout << "Start additing details\n";
        }
        if (strcmp(mes, "add_details_name") == 0)
        {
            bzero(mes, sizeof(mes));
            read(s, mes, sizeof(mes));

            std::cout << "  Detail's name:  " << mes << "\n";
        }
        if (strcmp(mes, "add_details_quant") == 0)
        {
            bzero(mes, sizeof(mes));
            read(s, mes, sizeof(mes));

            std::cout << "  Detail's quant: " << mes << "\n";
        }*/

    }

    close(s);
    return 0;
}