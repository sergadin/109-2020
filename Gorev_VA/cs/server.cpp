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
    char buf[1024]; // ����� ��� ������ ��������� �� ��������
    char mes[1024];
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
    server.sin_port = htons(1234); // ����
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
        ms = accept(as, 0, 0); // �������� ������ ���������� �� �������
        if (ms < 0)
        {
            perror("������ ��� ������ accept");
            exit(1);
        }
        for (int i = 0; i < 1024; i++)
        {
            if (buf[i] != 0)
                std::cout << "~" << i;
        }
        bzero(buf, sizeof(buf)); // �������� ����� ���������
        for (int i = 0; i < 1024; i++)
        {
            if (buf[i] != 0)
                std::cout << "~" << i;
        }
        read(ms, buf, sizeof(buf)); // ������ ��������� �� �������
        std::cout << write(ms, buf, sizeof(buf));
        std::cout << write(ms, buf, sizeof(buf));
        close(ms); // ��������� ���������� � ��������
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
    close( as ); // ��������� ���� 1234; ������� ������ �� ����� ������������
    return 0;
}

/*
ms = accept(as, 0, 0); // �������� ������ ���������� �� ������� 
bzero(buf, sizeof(buf)); // �������� ����� ��������� 
read(ms, buf, sizeof(buf)); // ������ ��������� �� ������� 
close(ms); // ��������� ���������� � ��������
printf("message is = %s\n", buf);
if (strcmp(buf, "quit") == 0) break;
*/
