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

        sscanf(buf, "%s", &mes);
        /*int a[256];
        a[0] = mes[0];
        a[1] = mes[1];
        a[2] = mes[2];
        a[3] = mes[3];
        a[4] = mes[4];
        printf("%d %d %d %d %d %c %c %c %c %c", a[0], a[1], a[2], a[3], a[4], mes[0], mes[1], mes[2], mes[3], mes[4]);*/
        if (strcmp(mes, "quit") == 0) break;
        cur = buf;
        for (int i = 0; i < 256; i++)
        {
            bzero(mes, sizeof(mes));
            sscanf(cur, "%s", &mes);
            printf("mes = %s, size = %d\n", mes, strlen(mes));
            cur = cur + strlen(mes);
            if (cur[0] == 0) break;
            while (cur[0] == ' ') cur = cur + 1;
            if (i == 255)
            {
                close(as);
                return -1;
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
