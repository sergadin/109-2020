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

    write(s, argv[3], strlen(argv[3])); // �������� �������
    close(s);
    return 0;
}