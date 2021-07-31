#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>


//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>


int main(int argc, char *argv[])
{
    int s;
    int Res;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[1024]; 

    if( argc<4 ) { return 1; }

    s = socket(AF_INET, SOCK_STREAM, 0 );
    if(s < 0)
    {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    bcopy( hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2])); 

    Res=connect(s, (struct sockaddr *)&server, sizeof(server));
    if(Res < 0)
    {
        perror("connect");
        return 2;
    }
//    write(s, argv[3], strlen(argv[3]) );
    send(s, argv[3], strlen(argv[3]), 0);

//printf("CP 1\n");
    while( 1 ) 
    {
//printf("CP 2\n");
        bzero( buf, sizeof(buf));
//        read(s, buf, sizeof(buf));
        recv(s, buf, sizeof(buf),0);
        if(strlen(buf)>0)printf("%s", buf );
        if ( strcmp(buf, "@Stop") == 0 ) break;
    }
//printf("CP 3\n");
printf("\n");

    close( s );
    return 0;
}
