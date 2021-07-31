#include "connector.h"
#include "autotest.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Error: too few arguments passed." << std::endl;
		return -1;
	}

	const std::string localhost = "127.0.0.1";
	int default_port = 8000;

	// Generating Instructions if needed
	//gen_instructions("Long_Instructions.txt", 10'000);

	// Running autotest if needed
	/*if (autotest("Long_Instructions.txt", "Short_1.txt", "Short_2.txt", localhost, default_port) == true)
	{
		std::cout << "Autotest passed successfully." << std::endl;
		std::cout << "* -------- * * -------- *" << std::endl;
	}*/

	connector C_1(localhost, default_port);

	C_1.polling();

	return 0;
}