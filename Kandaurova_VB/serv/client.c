#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char *argv[]){
    int			fd;
    struct addrinfo	hints;
    struct addrinfo	*result, *rp;
    int			retval;


    if (argc != 3) {
	fprintf(stderr, "Usage: %s host port\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = 0;
    hints.ai_protocol = 0;           

    retval = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (retval != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
	exit(EXIT_FAILURE);
    }
   
    for (rp = result; rp != NULL; rp = rp->ai_next) {
	fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (fd == -1) continue;
	if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) break;
	close(fd);
    }

    if (rp == NULL) {
	fprintf(stderr, "Could not connect\n");
	exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    while(1){
	char	s[80];
	ssize_t	retval;

	printf("message: ");
	memset(s, 0, sizeof(s));
	scanf("%78s", s);
	strcat(s, "\n");

	retval = write(fd, s, strlen(s));
	if (retval != strlen(s)){
	    if (retval < 0) printf("write error: %s\n", strerror(errno));
	    break;
	}
	retval = read(fd, s, sizeof(s) - 1);
	if (retval <= 0){
	    if (retval < 0) printf("read error: %s\n", strerror(errno));
	    break;
	}
	s[retval] = '\0';
	printf("server reply: %s\n", s);
    }

    close(fd);
    return 0;
}
