#ifndef SERVER
#define SERVER

#include "database.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring> // for memset

#define MAX_CLIENTS 10
#define SHUTDOWN_TIME 120
#define MAX_RECIEVE_BUFFER 8192

class server
{
private:
	database db;
	void request_wrap(int* client_socket, std::mutex& mtx); // Gets a client socket and works with it in independent thread
public:
	server(std::string server_address, int connection_port);
	~server();
};
// service function
unsigned int inet_addr(const char* str);

#endif//SERVER
