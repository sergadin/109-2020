//Для передачи матрицы на сервер клиент должен ввести строку вида: m[размер 1]*[размер 2]*[элемент матрицы 1]*[элемент матрицы 2]*...
//В ответ сервер выдаст максимальный элемент матрицы


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <errno.h>

#define COMPAT_SETSOCKOPT(x) x
#define MAX_CONNECTION	10

int main(int argc, char *argv[]){
    int			fd, client_cnt = 0;
    int			cfd[MAX_CONNECTION];
    struct addrinfo	hints;
    struct addrinfo	*result, *rp;
    int			retval, reuse_addr;
    double M, N, *matr;
    if (argc != 2) {
	fprintf(stderr, "Usage: %s port\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;     
    hints.ai_protocol = 0;           
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    retval = getaddrinfo(NULL, argv[1], &hints, &result);
    if (retval != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
	exit(EXIT_FAILURE);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
	fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (fd == -1) continue;
	reuse_addr=1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, COMPAT_SETSOCKOPT(&reuse_addr), sizeof(reuse_addr)) != 0) goto error;
	if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0) break;
      error:
	close(fd);
    }
    if (rp == NULL) {
	fprintf(stderr, "Could not bind\n");
	exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    if (listen(fd, 10) != 0){
	fprintf(stderr, "Could not listen, error: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
    }	
	
    while(1){
	fd_set	rfds;
	int	i, retval, max;
	FD_ZERO(&rfds);
	max = fd;
	FD_SET(fd, &rfds);
	for(i = 0; i < client_cnt; i++){
		if (cfd[i] > max) max = cfd[i];
		FD_SET(cfd[i], &rfds);
	}
	retval = select(max + 1, &rfds, NULL, NULL, NULL);
	if (retval == -1){
	    fprintf(stderr, "Could not select, error: %s\n", strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if (FD_ISSET(fd, &rfds)){
	    struct sockaddr_storage	peer_addr;
	    socklen_t			peer_addr_len;
	    char			host[NI_MAXHOST], service[NI_MAXSERV];
	    int				fd1;
	    peer_addr_len = sizeof(peer_addr);
	    fd1 = accept(fd, (struct sockaddr *) &peer_addr, &peer_addr_len);
	    if (fd1 != -1){
		retval = getnameinfo((struct sockaddr *) &peer_addr,
		                    peer_addr_len, host, NI_MAXHOST,
		                    service, NI_MAXSERV, NI_NUMERICSERV);
		if (retval == 0) printf("Received connection from %s:%s\n", host, service);
		else fprintf(stderr, "getnameinfo: %s\n", gai_strerror(retval));
		if (client_cnt < MAX_CONNECTION) cfd[client_cnt++] = fd1;
		else{
		    fprintf(stderr, "Max connections reached, drop new connection\n");
		    close(fd1);
		}
	    }
	}

	for(i = 0; i < client_cnt; i++){
	    ssize_t			bytes;
	    char			buf[1000];
            for(int j=0; j<1000; buf[j++]=' ');
	    if (!FD_ISSET(cfd[i], &rfds)) continue;
	    bytes = read(cfd[i], buf, sizeof(buf));
	    if (bytes <= 0){
		if (bytes < 0)
		    printf("read error: %s\n", strerror(errno));
		printf("close connection %d\n", i);
		close(cfd[i]);
		memmove(&cfd[i], &cfd[i + 1], (client_cnt - i - 1) * sizeof(int));
		client_cnt--;
		i--;
		continue;
	    }
	    if(buf[0] =='e') {
	    	close(fd);
	    	return 0;
	    }
	    if((buf[0] == 'm')) {
	    
		for(int i=0; i<1000;i++) {
			if(buf[i]=='*') 
				buf[i]=' ';
		}
	    	double next, maximum;	    	
	    	char *s1;
	    	double m = strtod (&buf[1], &s1);
         	double n = strtod (s1, &s1);
         	M = m;
         	N = n;
         	matr = (double *)realloc(NULL, n * m * sizeof(double));
         	maximum = strtod(s1, &s1);
         	matr[0] = maximum;
         	for(int j = 1; j < (m * n); j++) {
         		matr[j] = strtod (s1, &s1);
         		if(matr[j] > maximum)
         			maximum = matr[j];
         	}
         	sprintf(buf, "%f ", maximum);
         	write(cfd[i], buf, 40);	    
	    }
	    if(buf[0] == 'v') {
	    	for(int i=0; i<1000;i++) {
			if(buf[i]=='*') 
				buf[i]=' ';
		}
	    	char *s1;
	    	double n1 = strtod(&buf[1], &s1), x;
	    	//char *s1;
	    	if(n1 == N) {
	    		double *a = (double *)malloc(N * sizeof(double));
	    		for(int j = 0; j < n1; j++) 
	    			a[j] = strtod (s1, &s1);
	    		//printf("a = %f\n", a[0]);
	    		for(int j = 0; j < M; j++) {
	    			x = 0;
	    			for(int k = 0; k < N; k++) {
	    				x += matr[(int)M * j + k]*a[k];
	    				
	    			}
	    			//printf("%f\n", x);
	    			sprintf(buf, "%f*", x);
	    			printf("%79s\n", buf);
	    			//write(cfd[i], buf, 40);
	    		}
	    	}
	    	write(cfd[i], buf, 40);	
	    }
	    printf("connection %d: %s\n", i, buf);
	    write(cfd[i], "Ok.\n", 4);
	}
    }
    
    close(fd);
    return 0;
}
