#ifndef CONNECT
#define CONNECT

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <exception>
#include <sstream>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>



///	                                         Available commands:          

/*	1) "load_from_txt file.txt" - stores data to database from file.txt (client side) -- Ok --              */  /// Checked
/*	2) "save_to_txt file.txt" - saves data from database to file.txt (client side) -- Ok --                 */  /// Checked
/*	3) "add_course Name Hrs Hrs Hrs Hrs" - adds course "Name" with corresponding workload hours -- OK --    */  /// Checked
/*	4) "delete_course Name" - deletes course "Name" -- Ok --                                                */  /// Checked
/*	5) "add_staff Name Ncourses h1 ... h6 c1 ... cN" - adds staff with given hierarchy and courses -- OK -- */  /// Checked
/*	6) "delete_staff Name" - deletes staff "Name" from database -- Ok --                                    */  /// Checked
/*	7) "save_on_server file.txt" - saves data from database to file.txt (server_side) -- Ok --              */  /// Checked
/*	8) "get_course Name" - returns a course info -- Ok --                                                   */  /// Checked
/*	9) "get_staff Name" - returns a staff info -- Ok --                                                     */  /// Checked
/*	10) "update_course Name hrs hrs hrs hrs" - sets new hrs for course Name                                 */  /// Checked (~)
/*	11) "update_staff Name Ncourses h1...h6 c1...c6" - sets new hierarchy and courses for staff Name        */  /// Checked (~)
/*  13) "columns c1..ck for_all ..",where c1..ck may be Name,Lectures,Seminars,Colloqiums,Exams,row_sum     */  /// Checked
/*  14) "subcols --//-- " - forming columns in the same way from previous formed columns                    */  /// Checked
/*  15) "html_col name.html --//--" - saves a "columns" command result to a html file                       */  /// Checked
/*  16) "clear" - cleares database                                                                          */

/*  17) "help" - prints all available commands with descriptions                                            */  /// Checked




#define MAX_RECIEVE_BUFFER 15000

class connector
{
private:
	int connection_socket;
public:
	connector(std::string server_address, int connection_port);
	void request(std::string request_command, bool logs);
	void polling();
	void execute_instructions(std::string instructions_file);
	~connector();
};




class request_error : public std::exception
{
private:
	std::string error_msg;
public:
	request_error(std::string error_msg) { this->error_msg = error_msg; }
	const char* what() const noexcept override { return error_msg.c_str(); }
};

// service function
unsigned int inet_addr(const char* str);


#endif//CONNECT
