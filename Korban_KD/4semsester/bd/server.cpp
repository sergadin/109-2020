#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include "R2.hpp"
using namespace std;

int main(int argc, char** argv)
{
    int as, ms;
    struct sockaddr_in server;
    char buf[1024]; /* буфер для приема сообщений от клиентов */
    Database_R2 database;
    std::list<std::pair<Cell*, std::array<int, 2>>> result;
    database.read_file();
    database.to_file("to_file.txt");

    /* Создаем сокет для работы по TCP/IP */
    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        return -1;
    } 

    /* Заполняем структуру адреса, на котором будет работать сервер */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* любой сетевой интерфейс */
    server.sin_port = htons(atoi(argv[1])); /* порт */

    /* сопоставляем адрес с сокетом */
    if ((bind(as, (struct sockaddr*)&server, sizeof(server))) == -1)
    {
        perror("bind error");
        close( as );
        return -1;
    }

    /* сокет as используется для приема соединений; 5 - длина очереди */
    if ((listen(as, 5)) == -1)
    {
        perror("listen error");
        close( as );
        return -1;
    } 

    /* цикл обработки клиентов */
    while( 1 ) 
    {
        ms = accept( as, 0, 0 );/* выбираем первое соединение из очереди */
        while(1)
        {
            
            if (ms < 0)
            {
                perror("accept error");
                close( as );
                return -1;
            }

            bzero( buf, sizeof(buf)); /* обнуляем буфер сообщения */
            result.clear();

            read(ms, buf, sizeof(buf)); /* читаем сообщение от клиента */
            printf("message is = %s\n", buf );
            if ( ( strcmp(buf, "quit") == 0 )|| strcmp(buf, "") == 0) 
            {
                close( ms );

            }

            if ( ( strcmp(buf, "kill") == 0 )) 
            {
                close( ms );
                close( as );
                return 0;

            }

            string message(buf);

            int res = database.parce(buf,result);
            if(res != 0)
            {
                sprintf(buf, "%d", res);
                write(ms, buf, strlen(buf) );
            }
            
            if(res == 0)
            {
                /*string success = "SELECT sucsesfull\n";
                write(ms, success.c_str(), strlen(success.c_str()) );*/
                stringstream ss;
                for(pair<Cell*, array<int,2 >> data : result)
                {
                    ss <<"time: "<< data.second[0] <<" room: " <<data.second[1] << " teacher: " << data.first->get_teacher() << " course: " << data.first->get_course() 
                    << " group:"<< data.first->get_group() << endl;
                }
                write(ms, (to_string(res) + ss.str()).c_str(), strlen((to_string(res) + ss.str()).c_str()) );
            }
        }
    }
    
    close( as ); /* закрываем порт 1234; клиенты больше не могут подключаться */
    return 0;
}
