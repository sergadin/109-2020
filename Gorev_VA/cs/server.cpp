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
    char buf[1024]; // ����� ��� ������ ��������� �� ��������
    char mes[1024];
    int er_code = 0;
    //char *cur;
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
    server.sin_port = htons(1230); // ����
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
    while( 1 )
	{
        socklen_t size;
        size = sizeof(client);
        ms = accept(as, (struct sockaddr*)&client, &size); // �������� ������ ���������� �� �������
        if (ms < 0)
        {
            perror("������ ��� ������ accept");
            exit(1);
        }
        bzero(buf, sizeof(buf)); // �������� ����� ��������� 
        read(ms, buf, sizeof(buf)); // ������ ��������� �� �������
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

        close(ms); // ��������� ���������� � ��������
    }
    close( as ); // ��������� ���� 1234; ������� ������ �� ����� ������������
    return er_code;
}

/*
ms = accept(as, 0, 0); // �������� ������ ���������� �� ������� 
bzero(buf, sizeof(buf)); // �������� ����� ��������� 
read(ms, buf, sizeof(buf)); // ������ ��������� �� ������� 
close(ms); // ��������� ���������� � ��������
printf("message is = %s\n", buf);
if (strcmp(buf, "quit") == 0) break;
*/
