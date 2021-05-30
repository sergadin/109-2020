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
    char buf[1024]; /* ����� ��� ������ ��������� �� �������� */
    char mes[1024];
    char *cur;
    Base B;
    as = socket(AF_INET, SOCK_STREAM, 0 ); /* ������� ����� ��� ������ �� TCP/IP */
    /* ��������� ��������� ������, �� ������� ����� �������� ������ */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* ����� ������� ��������� */
    server.sin_port = htons(1234); /* ���� */

    /* ������������ ����� � ������� */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* ����� as ������������ ��� ������ ����������; 5 - ����� ������� */

    /* ���� ��������� �������� */
    while( 1 )
	{
        ms = accept(as, 0, 0); // �������� ������ ���������� �� ������� 
        bzero(buf, sizeof(buf)); // �������� ����� ��������� 
        read(ms, buf, sizeof(buf)); // ������ ��������� �� �������
        close(ms); // ��������� ���������� � ��������
        printf("message is = %s\n", buf);

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) break;
        cur = buf;
        while (cur[0] == ' ') cur = cur + 1;

        // ���� ��������� ������ ���������
        while (1)
        {
            // ������ ������ �������
            bzero(mes, sizeof(mes));
            if (cur[0] == 0) break;
            while (cur[0] == ' ') cur = cur + 1;
            sscanf(cur, "%s", &mes);
            cur = cur + strlen(mes);
            while (cur[0] == ' ') cur = cur + 1;
            printf("mes = %s, size = %d\n", mes, strlen(mes));

            // ���������� �������
            if (strcmp(mes, "add_details") == 0)
                while (1)
                {
                    // ������ �������� ������
                    bzero(mes, sizeof(mes));
                    if (cur[0] == 0) break;
                    while (cur[0] == ' ') cur = cur + 1;
                    sscanf(cur, "%s", &mes);
                    cur = cur + strlen(mes);
                    while (cur[0] == ' ') cur = cur + 1;
                    printf("detail = %s, size = %d\n", mes, strlen(mes));
                    std::string det_name(mes);
                    std::cout << det_name << " " << det_name.length() << "\n";
                    break;
                }

            if (cur[0] == 0) break;
        }
    }
    close( as ); /* ��������� ���� 1234; ������� ������ �� ����� ������������ */
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
