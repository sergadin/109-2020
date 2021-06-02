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
    server.sin_port = htons(1230); /* ���� */
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
        printf("message is = %s, Size = %d\n", buf, strlen(buf));

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) break;
        cur = buf;
        while (cur[0] == ' ') cur = cur + 1;

        // ���� ��������� ������ ���������
        while (1)
        {
            // ������ ������ �������
            scan_next(cur, mes);
            printf("  command = %s, size = %d\n", mes, strlen(mes));

            // ���������� �������
            if (strcmp(mes, "add_details") == 0)
                while (1)
                {
                    // ������ �������� ������ / ��������� �� ��������� ����������
                    if (scan_next(cur, mes) == -1) { close(as); return -1; }

                    if (strcmp(mes, "end") == 0)
                        break;
                    else
                    {
                        printf("    new detail = %s, ", mes);

                        // ������ ���������� �������
                        int det_quant;
                        if (scan_next(cur, det_quant) == -1) { close(as); return -1; }
                        printf("quant = %d\n", det_quant);

                        // ��������� ������ � ����
                        std::string det_name(mes);
                        B.add_detail(det_name, det_quant);
                    }
                }
            
            // ���������� �����
            if (strcmp(mes, "add_map") == 0)
            {
                std::vector <std::string> map;
                map.resize(1);

                // ������ �������� ������ ������
                bzero(mes, sizeof(mes));
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%s", &mes);
                cur = cur + strlen(mes);
                while (cur[0] == ' ') cur = cur + 1;
                std::string det_name0(mes);
                map[0] = det_name0;
                //std::cout << "<" << map[1] << ">";

                while (1)
                {
                    // ������ �������� ������ / ��������� �� ��������� ����������
                    bzero(mes, sizeof(mes));
                    if (cur[0] == 0) { close(as); return -1; }
                    while (cur[0] == ' ') cur = cur + 1;
                    sscanf(cur, "%s", &mes);
                    cur = cur + strlen(mes);
                    while (cur[0] == ' ') cur = cur + 1;
                    if (strcmp(mes, "end") == 0)
                        break;
                    else
                    {
                        std::string det_name1(mes);
                        map.resize(map.size() + 2);
                        map[map.size() - 2] = det_name1;
                        printf("    detail = %s, ", mes);
                        if (cur[0] == 0) { close(as); return -1; }

                        // ������ ���������� �������
                        bzero(mes, sizeof(mes));
                        if (sscanf(cur, "%s", &mes) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %s\n", mes);
                        std::string det_quant1(mes);
                        map[map.size() - 1] = det_quant1;
                    }
                }

                // ��������� ����� � ����
                B.add_map(map);
            }

            // ����� �� ������� ������ �� ����� �...
            if (strcmp(mes, "can_build_map_#") == 0)
            {
                // ������ ����� ����� (������� � �������)
                int map_num;
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%d", &map_num);
                while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                while (cur[0] == ' ') cur = cur + 1;

                // ������� ������� ������� ����� �������
                int det_kol = B.can_build_map(map_num);
                if (det_kol < 0) { close(as); return -1; }
                std::cout << "    can build " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
            }

            // ����� �� ������� ������ �� ����� ...
            if (strcmp(mes, "can_build_map") == 0)
            {
                std::vector <std::string> map;
                map.resize(1);

                // ������ �������� ������ ������
                bzero(mes, sizeof(mes));
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%s", &mes);
                cur = cur + strlen(mes);
                while (cur[0] == ' ') cur = cur + 1;
                std::string det_name0(mes);
                map[0] = det_name0;
                //std::cout << "<" << map[1] << ">";

                while (1)
                {
                    // ������ �������� ������ / ��������� �� ��������� ����������
                    bzero(mes, sizeof(mes));
                    if (cur[0] == 0) { close(as); return -1; }
                    while (cur[0] == ' ') cur = cur + 1;
                    sscanf(cur, "%s", &mes);
                    cur = cur + strlen(mes);
                    while (cur[0] == ' ') cur = cur + 1;
                    if (strcmp(mes, "end") == 0)
                        break;
                    else
                    {
                        std::string det_name1(mes);
                        map.resize(map.size() + 2);
                        map[map.size() - 2] = det_name1;
                        printf("    detail = %s, ", mes);
                        if (cur[0] == 0) { close(as); return -1; }

                        // ������ ���������� �������
                        bzero(mes, sizeof(mes));
                        if (sscanf(cur, "%s", &mes) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %s\n", mes);
                        std::string det_quant1(mes);
                        map[map.size() - 1] = det_quant1;
                    }
                }

                // ������� ������� ������� ����� �������
                int det_kol = B.can_build_map(map);
                if (det_kol < 0) { close(as); return -1; }
                std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
            }

            // ������� ������ �� �����
            if (strcmp(mes, "build_map_#") == 0)
            {
                // ������ ����� ����� (������� � �������)
                int map_num;
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%d", &map_num);
                while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                while (cur[0] == ' ') cur = cur + 1;

                // ������ ���������� ������� ������� ���� ������� 
                int map_kol;
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%d", &map_kol);
                while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                while (cur[0] == ' ') cur = cur + 1;

                // ������� ������� ������� ����� �������
                int det_kol = B.build_map(map_num, map_kol);
                if (det_kol < 0) { close(as); return -1; }
                std::cout << "    builded " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
            }

            // �������� ���������� ����
            if (strcmp(mes, "show_details") == 0)
                B.show_details();
            if (strcmp(mes, "show_maps") == 0)
                B.show_maps();
            if (strcmp(mes, "show_base") == 0)
                B.show_base();

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
