#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"

int write_mes(int ms, char* mes)
{
    char mes_len[1024];
    bzero(mes_len, sizeof(mes_len));

    int len = strlen(mes);
    sprintf(mes_len, "%d", len);
    write(ms, mes_len, sizeof(mes_len));

    write(ms, mes, len);
    return 0;
}

char* read_mes(int ms)
{
    char mes_len[1024];
    bzero(mes_len, sizeof(mes_len));
    read(ms, mes_len, sizeof(mes_len));
    int len = 0;
    sscanf(mes_len, "%d", &len);

    char* mes;
    mes = new char[len + 1];
    bzero(mes, len + 1);
    read(ms, mes, len);
    return mes;
}


int main(int argc, char* argv[])
{
    int s;
    struct sockaddr_in server;
    struct hostent* hp;

    if (argc < 4) { return 1; } // ������ ���� 3 ���������: �����, ���� � ���������

    // ������� ����� ��� ������ �� TCP/IP
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("������ ��� ������ socket");
        exit(1);
    }

    // ��������� �������� � ������� �������
    server.sin_family = AF_INET; // �������� IP
    hp = gethostbyname(argv[1]); // ���������� � DNS � ������ ����� �� ����������� �����
    bcopy(hp->h_addr, &server.sin_addr, hp->h_length); // �������� �� hp->h_addr � &server.sin_addr hp->h_length ����
    server.sin_port = htons(atoi(argv[2])); // ����� �����, �� ������� ������� ������

    // ������������� ���������� � ��������
    if ((connect(s, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("������ ��� ������ connect");
        exit(1);
    }

    write_mes(s, argv[3]); // �������� �������

    char* buf;
    buf = read_mes(s);
    std::cout << "Recieved message: " << buf << "\n";

    while (1)
    {
        delete[] buf;
        //bzero(buf, sizeof(buf));
        buf = read_mes(s);
        //std::cout << "  Command: " << buf << "\n";

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
            std::cout << "Error ";

            delete[] buf;
            buf = read_mes(s);
            int er_code = 0;
            sscanf(buf, "%d", &er_code);
            std::cout << er_code << "\n";
            
            std::cout << "  Error in: ";
            if ((er_code > 0) || (er_code < -21)) std::cout << "Unknown error\n";
            if (er_code == -1) std::cout << "add_details: reading of new detail's name\n";
            if (er_code == -2) std::cout << "add_details: reading of new detail's quant\n";
            if (er_code == -3) std::cout << "add_map: reading of result detail's name\n";
            if (er_code == -4) std::cout << "add_map: reading of component detail's name\n";
            if (er_code == -5) std::cout << "add_map: reading of component detail's quant\n";
            if (er_code == -6) std::cout << "can_build_map_#: reading of map's number\n";
            if (er_code == -7) std::cout << "can_build_map_#: calculating of number of details that can be builded\n";
            if (er_code == -8) std::cout << "can_build_map: reading of result detail's name\n";
            if (er_code == -9) std::cout << "can_build_map: reading of component detail's name\n";
            if (er_code == -10) std::cout << "can_build_map: reading of component detail's quant\n";
            if (er_code == -11) std::cout << "can_build_map: calculating of number of details that can be builded\n";
            if (er_code == -12) std::cout << "build_map_#: reading of map's number\n";
            if (er_code == -13) std::cout << "build_map_#: reading of number of details than must be builded\n";
            if (er_code == -14) std::cout << "build_map_#: calculating of number of details than can be builded\n";
            if (er_code == -15) std::cout << "read_from_file: reading of file's name\n";
            if (er_code == -16) std::cout << "read_from_file: opening of file\n";
            if (er_code == -17) std::cout << "del_details: reading of deleted detail's name\n";
            if (er_code == -18) std::cout << "del_details: reading of deleted detail's quant\n";
            if (er_code == -19) std::cout << "del_details: deleting\n";
            if (er_code == -20) std::cout << "write_in_file: reading of file's name\n";
            if (er_code == -21) std::cout << "write_in_file: opening of file\n";

            break;
        }
        if (strcmp(buf, "add_details") == 0)
        {
            std::cout << "  Start additing details\n";
            continue;
        }
        if (strcmp(buf, "add_details_name") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "  " << buf << ") ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << "Detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_details_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            for (int i = 0; i < (4 + strlen(buf)); i++)
                std::cout << " ";

            delete[] buf;
            buf = read_mes(s);
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
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Result detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_map_comp_name") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    " << buf << ") ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << "Component detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "add_map_comp_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            for (int i = 0; i < (2 + strlen(buf)); i++)
                std::cout << " ";

            delete[] buf;
            buf = read_mes(s);
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
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Number " << buf << ":\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_#_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    " << buf << " details ";

            delete[] buf;
            buf = read_mes(s);
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
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Result detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_comp_name") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    " << buf << ") ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << "Component detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_comp_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            for (int i = 0; i < (2 + strlen(buf)); i++)
                std::cout << " ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Component detailail's quant: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "can_build_map_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    " << buf << " details ";

            delete[] buf;
            buf = read_mes(s);
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
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Number " << buf << ":\n";
            continue;
        }
        if (strcmp(buf, "build_map_#_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Want build: " << buf << " details ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << buf << "\n";
            continue;
        }
        if (strcmp(buf, "build_map_#_builded") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Builded: " << buf << " details ";

            delete[] buf;
            buf = read_mes(s);
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
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Filename: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "read_from_file_close") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    File: " << buf << " closed\n";
            continue;
        }

        if (strcmp(buf, "show_details") == 0)
        {
            std::cout << "  List of details:\n";
            delete[] buf;
            buf = read_mes(s);
            
            int num;
            sscanf(buf, "%d", &num);
            for (int I = 0; I < num; I++)
            {
                delete[] buf;
                buf = read_mes(s);
                std::cout << "  " << I + 1 << ") Name: " << buf << ", ";

                delete[] buf;
                buf = read_mes(s);
                std::cout << "quant: " << buf << "\n";
            }
            continue;
        }
        
        if (strcmp(buf, "show_maps") == 0)
        {
            std::cout << "  List of maps:\n";
            delete[] buf;
            buf = read_mes(s);

            int Num;
            sscanf(buf, "%d", &Num);
            for (int I = 0; I < Num; I++)
            {
                delete[] buf;
                buf = read_mes(s);
                std::cout << "  " << I + 1 << ") Name: " << buf << "\n";

                int num;
                delete[] buf;
                buf = read_mes(s);
                sscanf(buf, "%d", &num);
                for (int i = 1; i <= num; i++)
                {
                    delete[] buf;
                    buf = read_mes(s);
                    std::cout << "    " << I + 1 << ". Name: " << buf << ", ";

                    delete[] buf;
                    buf = read_mes(s);
                    std::cout << "quant: " << buf << "\n";
                }
            }
            continue;
        }

        if (strcmp(buf, "del_details") == 0)
        {
            std::cout << "  Start deleting details\n";
            continue;
        }
        if (strcmp(buf, "del_details_name") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "  " << buf << ") ";

            delete[] buf;
            buf = read_mes(s);;
            std::cout << "Detailail's name: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "del_details_quant") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            for (int i = 0; i < (4 + strlen(buf)); i++)
                std::cout << " ";

            delete[] buf;
            buf = read_mes(s);
            std::cout << "Detailail's quant: " << buf << "\n";
            continue;
        }

        if (strcmp(buf, "write_in_file") == 0)
        {
            std::cout << "  Start writing base in file:\n";
            continue;
        }
        if (strcmp(buf, "write_in_file_open") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    Filename: " << buf << "\n";
            continue;
        }
        if (strcmp(buf, "write_in_file_close") == 0)
        {
            delete[] buf;
            buf = read_mes(s);
            std::cout << "    File: " << buf << " closed\n";
            continue;
        }
    }

    delete[] buf;
    close(s);
    return 0;
}