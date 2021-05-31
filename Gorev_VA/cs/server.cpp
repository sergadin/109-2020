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
	printf("starting");
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; /* áóôåð äëÿ ïðèåìà ñîîáùåíèé îò êëèåíòîâ */
    char mes[1024];
    char *cur;
    Base B;
    as = socket(AF_INET, SOCK_STREAM, 0 ); /* Ñîçäàåì ñîêåò äëÿ ðàáîòû ïî TCP/IP */
    /* Çàïîëíÿåì ñòðóêòóðó àäðåñà, íà êîòîðîì áóäåò ðàáîòàòü ñåðâåð */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* ëþáîé ñåòåâîé èíòåðôåéñ */
    server.sin_port = htons(1234); /* ïîðò */

    /* ñîïîñòàâëÿåì àäðåñ ñ ñîêåòîì */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* ñîêåò as èñïîëüçóåòñÿ äëÿ ïðèåìà ñîåäèíåíèé; 5 - äëèíà î÷åðåäè */
	printf("sstarting");
    /* öèêë îáðàáîòêè êëèåíòîâ */
    while( 1 )
	{
        ms = accept(as, 0, 0); // âûáèðàåì ïåðâîå ñîåäèíåíèå èç î÷åðåäè 
        bzero(buf, sizeof(buf)); // îáíóëÿåì áóôåð ñîîáùåíèÿ 
        read(ms, buf, sizeof(buf)); // ÷èòàåì ñîîáùåíèå îò êëèåíòà
        close(ms); // çàêðûâàåì ñîåäèíåíèå ñ êëèåíòîì
        printf("message is = %s\n", buf);

        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        if (strcmp(mes, "quit") == 0) break;
        cur = buf;
        while (cur[0] == ' ') cur = cur + 1;

        // öèêë îáðàáîòêè îäíîãî ñîîáùåíèÿ
        while (1)
        {
            // ÷èòàåì ïåðâóþ êîìàíäó
            bzero(mes, sizeof(mes));
            if (cur[0] == 0) break;
            while (cur[0] == ' ') cur = cur + 1;
            sscanf(cur, "%s", &mes);
            cur = cur + strlen(mes);
            while (cur[0] == ' ') cur = cur + 1;
            printf("  command = %s, size = %d\n", mes, strlen(mes));

            // äîáàâëåíèå äåòàëåé
            if (strcmp(mes, "add_details") == 0)
                while (1)
                {
                    // ÷èòàåì íàçâàíèå äåòàëè / ñîîáùåíèå îá îêîí÷èíèè äîáàâëåíèÿ
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
                        printf("    new detail = %s, ", mes);
                        std::string det_name(mes);

                        if (cur[0] == 0) { close(as); return -1; }
                    
                        // ÷èòàåì êîëè÷åñòâî äåòàëåé
                        int det_quant;
                        if (sscanf(cur, "%d", &det_quant) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %d\n", det_quant);

                        // äîáàâëÿåì äåòàëè â áàçó
                        B.add_detail(det_name, det_quant);
                    }
                }
            
            // äîáàâëåíèå êàðòû
            if (strcmp(mes, "add_map") == 0)
            {
                std::vector <std::string> map;
                map.resize(1);

                // ÷èòàåì íàçâàíèå ïåðâîé äåòàëè
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
                    // ÷èòàåì íàçâàíèå äåòàëè / ñîîáùåíèå îá îêîí÷èíèè äîáàâëåíèÿ
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

                        // ÷èòàåì êîëè÷åñòâî äåòàëåé
                        bzero(mes, sizeof(mes));
                        if (sscanf(cur, "%s", &mes) != 1) { close(as); return -1; }
                        while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                        while (cur[0] == ' ') cur = cur + 1;
                        printf("quant = %s\n", mes);
                        std::string det_quant1(mes);
                        map[map.size() - 1] = det_quant1;
                    }
                }

                // äîáàâëÿåì êàðòó â áàçó
                //std::cout << "<" << map[1] << ">";
                B.add_map(map);
            }

            // ìîæíî ëè ñîçäàòü äåòàëü ïî êàðòå ¹...
            if (strcmp(mes, "can_build_#") == 0)
            {
                // ÷èòàåì íîìåð êàðòû (ïîðÿäîê ñ åäèíèöû)
                int map_num;
                if (cur[0] == 0) { close(as); return -1; }
                while (cur[0] == ' ') cur = cur + 1;
                sscanf(cur, "%d", &map_num);
                while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
                while (cur[0] == ' ') cur = cur + 1;

                // ñ÷èòàåì ñêîëüêî äåòàëåé ìîæíî ñîçäàòü
                int det_kol = B.can_build(map_num - 1);
                if (det_kol < 0) { close(as); return -1; }
                printf("can build %d details '%s'\n", det_kol, B.name[B.map[map_num - 1][0]]);
            }

            // ïîêàçàòü êîìïîíåíòû áàçû
            if (strcmp(mes, "show_details") == 0)
                B.show_details();
            if (strcmp(mes, "show_maps") == 0)
                B.show_maps();
            if (strcmp(mes, "show_base") == 0)
                B.show_base();

            if (cur[0] == 0) break;
        }
    }
    close( as ); /* çàêðûâàåì ïîðò 1234; êëèåíòû áîëüøå íå ìîãóò ïîäêëþ÷àòüñÿ */
    return 0;
}

/*
ms = accept(as, 0, 0); // âûáèðàåì ïåðâîå ñîåäèíåíèå èç î÷åðåäè 
bzero(buf, sizeof(buf)); // îáíóëÿåì áóôåð ñîîáùåíèÿ 
read(ms, buf, sizeof(buf)); // ÷èòàåì ñîîáùåíèå îò êëèåíòà 
close(ms); // çàêðûâàåì ñîåäèíåíèå ñ êëèåíòîì
printf("message is = %s\n", buf);
if (strcmp(buf, "quit") == 0) break;
*/
