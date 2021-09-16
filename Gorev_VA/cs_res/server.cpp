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
    char* buf; // ����� ��� ������ ��������� �� ��������
    char mes[1024];
    int er_code = 0;
    Base B;

    // ������� ����� ��� ������ �� TCP/IP 
    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("������ ��� ������ socket");
        exit(1);
    }
    // ������� �� ���� ������ ��������������
    int on = 1;
    if (setsockopt(as, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) == -1) {
        perror("������ ��� ������ setsockopt");
    }
    // ��������� ��������� ������, �� ������� ����� �������� ������
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; // ����� ������� ���������
    server.sin_port = htons(1231); // ����
    // ������������ ����� � �������
    if ((bind(as, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("������ ��� ������ bind");
        exit(1);
    }

    // ����� as ������������ ��� ������ ����������; 5 - ����� �������
    if ((listen(as, 5)) == -1)
    {
        perror("������ ��� ������ listen");
        exit(1);
    }

    // ���� ��������� ��������
    while(1)
	{
        ms = accept(as, 0, 0); // �������� ������ ���������� �� �������
        if (ms < 0)
        {
            perror("������ ��� ������ accept");
            exit(1);
        }
        //buf = new char[1];
        //bzero(buf, 1); // �������� ����� ���������
        buf = read_mes(ms); // ������ ��������� �� �������
        std::cout << "|" << buf << "|\n";
        write_mes(ms, buf);
        
        printf("message is = %s, Size = %d\n", buf, strlen(buf));

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0)
        {
            write_mes(ms, buf);
            delete[] buf;
            close(ms);
            break;
        }

        std::istringstream in(buf);
        er_code = B.do_from(in, ms);
        if (er_code < 0)
        {
            std::cout << "~~~~" << er_code << "\n";
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", er_code);
            write_mes(ms, mes);
        }

        delete[] buf;
        close(ms); // ��������� ���������� � ��������
    }
    close(as); // ��������� ���� 1234; ������� ������ �� ����� ������������
    return 0;
}
