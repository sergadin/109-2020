#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; /* ����� ��� ������ ��������� �� �������� */

    as = socket(AF_INET, SOCK_STREAM, 0 ); /* ������� ����� ��� ������ �� TCP/IP */

    /* ��������� ��������� ������, �� ������� ����� �������� ������ */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* ����� ������� ��������� */
    server.sin_port = htons(1234); /* ���� */

    /* ������������ ����� � ������� */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* ����� as ������������ ��� ������ ����������; 5 - ����� ������� */

    /* ���� ��������� �������� */
    while( 1 ) {
        ms = accept( as, 0, 0 ); /* �������� ������ ���������� �� ������� */
        bzero( buf, sizeof(buf)); /* �������� ����� ��������� */
        read(ms, buf, sizeof(buf)); /* ������ ��������� �� ������� */
        close( ms ); /* ��������� ���������� � �������� */
        printf("message is = %s\n", buf );
        if ( strcmp(buf, "quit") == 0 ) break;
    }
    close( as ); /* ��������� ���� 1234; ������� ������ �� ����� ������������ */
    return 0;
}
