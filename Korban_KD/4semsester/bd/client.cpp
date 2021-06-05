#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    int s;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[100000];

    //if( argc<4 ) { return 1; } /* должно быть 3 аргумента: адрес, порт и сообщение */

    /* Создаем сокет для работы по TCP/IP */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        return -1;
    }; 

    /* Заполняем струтуру с адресом сервера */
    server.sin_family = AF_INET; /* протокол IP */
    hp = gethostbyname("localhost"); /* Обращаемся к DNS и узнаем адрес по символьному имени*/
    bcopy( hp->h_addr, &server.sin_addr, hp->h_length); /* копируем из hp->h_addr в &server.sin_addr hp->h_length байт */
    server.sin_port = htons(atoi(argv[1])); /* номер порта, на котором запущен сервер */


    /* устанавливаем соединение с сервером */
    if ((connect(s, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("Îøèáêà ïðè âûçîâå connect");
        close(s);
        return -1;
    } 
    while(1)
    {   
        bzero(buf,sizeof(buf));
        string command;
        std::getline(std::cin, command);

        if((command == "quit"))
            break;
        
        if((command == "kill"))
        {
            write(s, command.c_str(), strlen(command.c_str()) );
            break;
        }
        //cout << command <<endl;
        write(s, command.c_str(), strlen(command.c_str()) );

        read(s, buf, sizeof(buf));
        if(buf[0] == '0')
        {
            printf("%s\n", buf + 1);
        }
        else
        {
            //printf("%s\n", buf);
            if(strcmp(buf, "-1") == 0)
            {
                cout << "wrong request" << endl;
            }

            if(strcmp(buf, "-2") ==0)
            {
                cout << "Cell allready exists" << endl;
            }
            if(strcmp(buf, "-10") ==0)
            {
                cout << "wrong command" << endl;
            }

        }

    }
    //write(s, argv[3], strlen(argv[3]) ); /* посылаем строчку */
    close( s );
    return 0;
}