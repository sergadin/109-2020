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
    char buf[1024]; /* áóôåð äëÿ ïðèåìà ñîîáùåíèé îò êëèåíòîâ */
    Base B;

    as = socket(AF_INET, SOCK_STREAM, 0 ); /* Ñîçäàåì ñîêåò äëÿ ðàáîòû ïî TCP/IP */

    /* Çàïîëíÿåì ñòðóêòóðó àäðåñà, íà êîòîðîì áóäåò ðàáîòàòü ñåðâåð */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* ëþáîé ñåòåâîé èíòåðôåéñ */
    server.sin_port = htons(1234); /* ïîðò */

    /* ñîïîñòàâëÿåì àäðåñ ñ ñîêåòîì */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* ñîêåò as èñïîëüçóåòñÿ äëÿ ïðèåìà ñîåäèíåíèé; 5 - äëèíà î÷åðåäè */

    /* öèêë îáðàáîòêè êëèåíòîâ */
    while( 1 )
	{
        ms = accept(as, 0, 0); // âûáèðàåì ïåðâîå ñîåäèíåíèå èç î÷åðåäè 
        bzero(buf, sizeof(buf)); // îáíóëÿåì áóôåð ñîîáùåíèÿ 
        read(ms, buf, sizeof(buf)); // ÷èòàåì ñîîáùåíèå îò êëèåíòà
        close(ms); // çàêðûâàåì ñîåäèíåíèå ñ êëèåíòîì
        printf("message is = %s\n", buf);

        char mes[1024];
        bzero(mes, sizeof(mes));
        sscanf(buf, "%s", &mes);
        printf("mes = %s\n", mes);
        if (strcmp(mes, "quit") == 0) break;
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
