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

int main()
{
    int s;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[100000];

    //if( argc<4 ) { return 1; } /* должно быть 3 аргумента: адрес, порт и сообщение */

    s = socket(AF_INET, SOCK_STREAM, 0 ); /* Создаем сокет для работы по TCP/IP */

    /* Заполняем струтуру с адресом сервера */
    server.sin_family = AF_INET; /* протокол IP */
    hp = gethostbyname("localhost"); /* Обращаемся к DNS и узнаем адрес по символьному имени*/
    bcopy( hp->h_addr, &server.sin_addr, hp->h_length); /* копируем из hp->h_addr в &server.sin_addr hp->h_length байт */
    server.sin_port = htons(8877); /* номер порта, на котором запущен сервер */

    connect(s, (struct sockaddr *)&server, sizeof(server)); /* устанавливаем соединение с сервером */
    while(1)
    {   
        bzero(buf,sizeof(buf));
        string command;
        std::getline(std::cin, command);
        
        cout << command <<endl;
        write(s, command.c_str(), strlen(command.c_str()) );
        read(s, buf, sizeof(buf));
        printf("message is = %s\n", buf );

    }
    //write(s, argv[3], strlen(argv[3]) ); /* посылаем строчку */
    close( s );
    return 0;
}