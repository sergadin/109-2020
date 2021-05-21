#include "server.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Error: too few arguemnts passed." << std::endl;
		return -1;
	}

	server S("127.0.0.1", 8000);

	return 0;
}
