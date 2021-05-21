#include "server.h"

unsigned int inet_addr(const char* str)
{
	int a, b, c, d;
	char arr[4];
	sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
	arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
	return *(unsigned int*)arr;
}

server::server(std::string server_address, int connection_port)
{
	std::cout << "Starting up server at <" << server_address << ":" << connection_port << ">." << std::endl;
	int response_code;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(connection_port);
	addr.sin_addr.s_addr = inet_addr(server_address.c_str());

	// Creating listening socket to process lient connections

	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket < 0)
	{
		std::cout << "Creating socket failed with code <" << listen_socket << ">" << std::endl;
		exit(-1);
	}


	// Binding listening socket:
	response_code = bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr));

	if (response_code < 0)
	{
		std::cout << "Bind failed" << std::endl;
		close(listen_socket);
		exit(-1);
	}

	// Listening on a socket to pending connection requests
	std::cout << "Waiting for connection requests..." << std::endl;

	response_code = listen(listen_socket, MAX_CLIENTS);
	if (response_code < 0)
	{
		std::cout << "Failed to set listening socket with code <" << response_code << ">" << std::endl;
		close(listen_socket);
		exit(-1);
	}

	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET(listen_socket, &socket_set);
	struct timeval tv = { 0 };
	tv.tv_sec = static_cast<long>(SHUTDOWN_TIME);

	std::vector<std::thread> thread_pool;
	std::vector<int*> client_sockets;
	std::mutex db_request_mutex;

	while (true)
	{
		fd_set tmp = socket_set;
		int select_status = select(FD_SETSIZE, &tmp, nullptr, nullptr, &tv);

		if (select_status == 0)
		{
			std::cout << "Connection timeout: no more clients can connect to server." << std::endl;
			break;
		}
		if (select_status < 0)
		{
			std::cout << "Select failed with code <" << select_status << ">" << std::endl;
			break;
		}
		int* client_sock = new int;
		*(client_sock) = accept(listen_socket, nullptr, nullptr);
		client_sockets.push_back(client_sock);

		thread_pool.push_back(std::thread(&server::request_wrap, this, client_sockets[client_sockets.size() - 1], std::ref(db_request_mutex)));
	}
	// Waiting for threads
	for (auto th = thread_pool.begin(); th != thread_pool.end(); ++th)
	{
		th->join();
	}
	std::cout << "Thread pool joined." << std::endl;

	for (auto socket_ptr = client_sockets.begin(); socket_ptr != client_sockets.end(); ++socket_ptr)
	{
		delete* (socket_ptr);
	}
	close(listen_socket);
}

void server::request_wrap(int* client_socket, std::mutex& mtx)
{
	char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
	mtx.lock();
	std::cout << "Thread " << std::this_thread::get_id() << ": successfully connected to client." << std::endl;
	mtx.unlock();
	while (true)
	{
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		int response_code = recv(*client_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code > 0)
		{
			std::stringstream r_stream;
			int i = 0;
			while (recieve_buffer[i] != 0) r_stream << recieve_buffer[i], ++i;
			// Passing request to database
			try
			{
				mtx.lock();
				std::string database_response = db.handle_request(r_stream.str());
				mtx.unlock();
				if (database_response != "Ok")
				{
					response_code = send(*client_socket, database_response.c_str(), strlen(database_response.c_str()), 0);
					if (response_code < 0)
					{
						mtx.lock();
						std::cout << "Thread " << std::this_thread::get_id() << ": failed to send response to client." << std::endl;
						mtx.unlock();
						close(*client_socket);
						break;
					}
				}
			}
			catch (const std::exception& exc)
			{
				std::stringstream e_stream;
				e_stream << "Thread " << std::this_thread::get_id() << ": error occured while handling request: <" << exc.what() << ">";
				std::cout << e_stream.str() << std::endl;
				response_code = send(*client_socket, (e_stream.str()).c_str(), strlen((e_stream.str()).c_str()), 0);
				if (response_code < 0)
				{
					mtx.lock();
					std::cout << "Thread " << std::this_thread::get_id() << ": failed to send error report to client." << std::endl;
					mtx.unlock();
					close(*client_socket);
					break;
				}
			}
		}
		else if (response_code == 0)
		{
			mtx.lock();
			std::cout << "Thread " << std::this_thread::get_id() << ": session complete." << std::endl;
			mtx.unlock();
			close(*client_socket);
			break;
		}
		else
		{
			mtx.lock();
			std::cout << "Thread " << std::this_thread::get_id() << ": failed to recieve data from client." << std::endl;
			mtx.unlock();
			close(*client_socket);
			break;
		}
	}
	delete[] recieve_buffer;
}

server::~server()
{
	std::cout << "Server shut down." << std::endl;
}