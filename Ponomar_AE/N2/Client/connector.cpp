#include "connector.h"

// service function 
unsigned int inet_addr(const char* str)
{
	int a, b, c, d;
	char arr[4];
	sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
	arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
	return *(unsigned int*)arr;
}

connector::connector(std::string server_address, int connection_port)
{
	int response_code;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(connection_port);
	addr.sin_addr.s_addr = inet_addr(server_address.c_str());

	// Initializing connection socket
	connection_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (connection_socket < 0)
	{
		std::cout << "Failed to initilize connection socket with code <" << connection_socket << ">" << std::endl;
		exit(-1);
	}

	// Connecting to server
	response_code = connect(connection_socket, (struct sockaddr*)&addr, sizeof(addr));

	if (response_code < 0)
	{
		std::cout << "Connection to server failed with code <" << response_code << ">" << std::endl;
		close(connection_socket);
		exit(-1);
	}

	// Address info is no longer needed
	std::cout << "Successfully connected to <" << server_address << ":" << connection_port << ">" << std::endl;
}

void connector::request(std::string request_command, bool logs)
{
	if (request_command.find("load_from_txt") != std::string::npos)
	{
		std::ifstream input_file;
		input_file.open(request_command.substr(14, request_command.size() - 1));
		if (!input_file.is_open())
		{
			throw request_error("Failed to open database file.");
		}
		int course_count = 0;
		input_file >> course_count;
		for (int course_num = 0; course_num < course_count; ++course_num)
		{
			std::stringstream course_ss;
			course_ss << "add_course ";
			std::string course_name;
			input_file >> course_name;
			course_ss << course_name;
			for (int hr_num = 0; hr_num < 4; ++hr_num)
			{
				int hours = 0;
				input_file >> hours;
				course_ss << " " << hours;
			}
			// Microsleep to avoid sticking tcp-packages together
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			int response_code = send(connection_socket, (course_ss.str()).c_str(), strlen((course_ss.str()).c_str()), 0);
			if (response_code < 0)
			{
				throw request_error("Failed to send request to server.");
			}
		}
		int staff_count = 0;
		input_file >> staff_count;
		for (int staff_num = 0; staff_num < staff_count; ++staff_num)
		{
			std::stringstream staff_ss;
			staff_ss << "add_staff ";
			std::string staff_name;
			input_file >> staff_name;
			staff_ss << staff_name;
			int course_number = 0;
			input_file >> course_number;
			staff_ss << " " << course_number;
			for (int hierarchy_code = 0; hierarchy_code < 6; ++hierarchy_code)
			{
				int hc = 0;
				input_file >> hc;
				staff_ss << " " << hc;
			}
			for (int course_num = 0; course_num < course_number; ++course_num)
			{
				int course_index = 0;
				input_file >> course_index;
				staff_ss << " " << course_index;
			}
			// Microsleep to avoid sticking tcp-packages together
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			int response_code = send(connection_socket, staff_ss.str().c_str(), strlen(staff_ss.str().c_str()), 0);
			if (response_code < 0)
			{
				throw request_error("Failed to send data to server.");
			}
		}
		if (logs) std::cout << "Loaded database from file successfully." << std::endl;
		input_file.close();
	}
	else if (request_command.find("save_to_txt") != std::string::npos)
	{
		std::ofstream output_file;
		output_file.open(request_command.substr(12, request_command.size() - 1));
		if (!output_file.is_open())
		{
			throw request_error("Error: cannot open file.");
		}
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		const char* database_request = "get_full_database";
		// Sending request to database
		int response_code = send(connection_socket, database_request, strlen(database_request), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to recieve data from server.");
		}
		for (int i = 0; i < static_cast<int>(MAX_RECIEVE_BUFFER); ++i)
		{
			if (recieve_buffer[i] != 0) output_file << recieve_buffer[i];
		}
		output_file.close();
		if (logs) std::cout << "Saved database to file successfully." << std::endl;
		delete[] recieve_buffer;
	}
	else if (request_command.find("add_course") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		if (logs) std::cout << "Course added." << std::endl;
	}
	else if (request_command.find("add_staff") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		if (logs) std::cout << "Staff added." << std::endl;
	}
	else if (request_command.find("delete_course") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
	}
	else if (request_command.find("delete_staff") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
	}
	else if (request_command.find("save_on_server") != std::string::npos)
	{
		std::stringstream ss;
		ss << "save " << request_command.substr(15, request_command.size() - 1);
		int response_code = send(connection_socket, ss.str().c_str(), strlen(ss.str().c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to database.");
		}
		if (logs) std::cout << "Successfully saved database on server." << std::endl;
	}
	else if (request_command.find("get_course") != std::string::npos)
	{
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		const char* database_request = request_command.c_str();
		int response_code = send(connection_socket, database_request, strlen(database_request), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Filed to recieve data from server.");
		}
		std::stringstream course_ss;
		int i = 0;
		while (recieve_buffer[i] != 0)
		{
			course_ss << recieve_buffer[i];
			i++;
		}
		if (logs) std::cout << course_ss.str() << std::endl;
		delete[] recieve_buffer;
	}
	else if (request_command.find("get_staff") != std::string::npos)
	{
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		const char* database_request = request_command.c_str();
		int response_code = send(connection_socket, database_request, strlen(database_request), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Filed to recieve data from server.");
		}
		std::stringstream staff_ss;
		int i = 0;
		while (recieve_buffer[i] != 0)
		{
			staff_ss << recieve_buffer[i];
			i++;
		}
		if (logs) std::cout << staff_ss.str() << std::endl;
		delete[] recieve_buffer;
	}
	else if (request_command.find("inspect_database") != std::string::npos)
	{
		const char* req = "print";
		int response_code = send(connection_socket, req, strlen(req), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to recieve data from server.");
		}
		std::stringstream db_ss;
		int i = 0;
		while (recieve_buffer[i] != 0)
		{
			db_ss << recieve_buffer[i];
			i++;
		}
		if (logs) std::cout << db_ss.str();
		delete[] recieve_buffer;
	}
	else if (request_command.find("update_course") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		if (logs) std::cout << "Course updated." << std::endl;
	}
	else if (request_command.find("update_staff") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		if (logs) std::cout << "Staff updated." << std::endl;
	}
	else if (request_command.find("columns") != std::string::npos)
	{
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		int response_code = send(connection_socket, (request_command.c_str()), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to recieve data from server.");
		}
		std::stringstream recieve_ss;
		int i = 0;
		while (recieve_buffer[i] != 0) recieve_ss << recieve_buffer[i], i++;
		if (logs) std::cout << recieve_ss.str() << std::endl;
	}
	else if (request_command.find("subcols") != std::string::npos)
	{
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		int response_code = send(connection_socket, (request_command.c_str()), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to recieve data from server.");
		}
		std::stringstream recieve_ss;
		int i = 0;
		while (recieve_buffer[i] != 0) recieve_ss << recieve_buffer[i], i++;
		if (logs) std::cout << recieve_ss.str() << std::endl;
		delete[] recieve_buffer;
	}
	else if (request_command.find("html_col") != std::string::npos)
	{
		std::ofstream output_html;
		output_html.open("DataTable.html");
		if (!output_html.is_open())
		{
			throw request_error("Failed to open html file.");
		}
		char* recieve_buffer = new char[static_cast<int>(MAX_RECIEVE_BUFFER)];
		memset(recieve_buffer, 0, static_cast<int>(MAX_RECIEVE_BUFFER));
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		response_code = recv(connection_socket, recieve_buffer, static_cast<int>(MAX_RECIEVE_BUFFER), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to receive data from server.");
		}
		std::stringstream recieve_ss;
		int i = 0;
		while (recieve_buffer[i] != 0) recieve_ss << recieve_buffer[i], i++;
		output_html << recieve_ss.str();
		output_html.close();
		if (logs) std::cout << "Saved data to html file successfully." << std::endl;
		delete[] recieve_buffer;
	}
	else if (request_command.find("clear") != std::string::npos)
	{
		int response_code = send(connection_socket, request_command.c_str(), strlen(request_command.c_str()), 0);
		if (response_code < 0)
		{
			throw request_error("Failed to send request to server.");
		}
		if (logs) std::cout << "Database cleared." << std::endl;
	}
	else if (request_command.find("help") != std::string::npos)
	{
		std::cout << " * ------- * * ------- *" << std::endl;
		std::cout << "Available commands:" << std::endl;
		std::cout << "1) 'load_from_txt  File.txt' - loads a database from *.txt file (Format as in example given)" << std::endl;
		std::cout << "2) 'save_to_txt File.txt' - saves a database in *.txt file (on client side)" << std::endl;
		std::cout << "3) 'add_course Name H1 H2 H3 H4' - adds a course with given name and hours" << std::endl;
		std::cout << "4) 'add_staff Name Ncourses H1...H6 C1...CN' - adds a staff with givem name, hierarchy code and courses" << std::endl;
		std::cout << "5) 'delete_course Name' - deletes course with corresponding name if such was found" << std::endl;
		std::cout << "6) 'delete_staff Name' - deletes staff with corresponding name if such was found" << std::endl;
		std::cout << "7) 'update_course Name H1 H2 H3 H4' - updates corresponding course with given hours" << std::endl;
		std::cout << "8) 'update_staff Name NCourses H1...H6 C1...CN' - updated staff with new hierarchy code and courses" << std::endl;
		std::cout << "9) 'save_on_server File.txt' - saves database on server side in *.txt file" << std::endl;
		std::cout << "10) 'get_course Name' - prints info about asked course" << std::endl;
		std::cout << "11) 'get_staff Name' - prints info about asked staff" << std::endl;
		std::cout << "12) 'columns C1 ... CN for_all H1...H6' - prints asked columns about staff with satisfying hierarchy" << std::endl;
		std::cout << "13) 'subcols --//--' - prints asked columns about staff with satisfying hierarchy using previous request" << std::endl;
		std::cout << "14) 'html_col --//--' - saves asked columns about staff with satisfying hierarchy in html table in file 'DataTable.html'" << std::endl;
		std::cout << "15) 'inspect_database' - prints whole database" << std::endl;
		std::cout << "16) 'clear' - cleares database" << std::endl;
		std::cout << "17) 'end' - disconnects from server" << std::endl;
		std::cout << " * ------- * * ------- *" << std::endl;
	}
	else
	{
		throw request_error("Error: unknown request command! Try again.");
	}
}

void connector::polling()
{
	std::cout << "Session started. To end session, type 'end'." << std::endl;
	while (true)
	{
		std::cout << "Enter request: ";
		std::string request_line;
		std::getline(std::cin, request_line);
		if (request_line == "end")
		{
			std::cout << "Ending session." << std::endl;
			break;
		}
		try
		{
			request(request_line, true);
		}
		catch (const std::exception& exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}
}

void connector::execute_instructions(std::string instructions_file)
{
	std::ifstream instr_file;
	instr_file.open(instructions_file);
	if (!instr_file.is_open())
	{
		std::cout << "Error: failed to open instructions file." << std::endl;
		exit(-1);
	}
	std::string line;
	while (std::getline(instr_file, line))
	{
		std::this_thread::sleep_for(std::chrono::microseconds(15));
		request(line, false);
	}
	std::cout << "Instrutions evaluated successfully" << std::endl;
	instr_file.close();
}

connector::~connector()
{
	close(connection_socket);
	std::cout << "Connection closed successfully." << std::endl;
}