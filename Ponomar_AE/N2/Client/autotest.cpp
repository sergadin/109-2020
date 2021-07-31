#include "autotest.h"

void gen_instructions(std::string output_file, int instructions_number)
{
	std::ofstream output;
	output.open(output_file);
	if (!output.is_open())
	{
		std::cout << "Failed to open file." << std::endl;
		exit(-1);
	}
	srand(time(nullptr));
	for (int i = 0; i < instructions_number; ++i)
	{
		std::stringstream instr_ss;
		int add_choice = rand() % 2;
		if (add_choice == 0)
		{
			instr_ss << "add_course Course_" << i;
			for (int j = 0; j < 4; ++j)
			{
				instr_ss << " " << rand() % 150;
			}
			output << instr_ss.str() << std::endl;
		}
		else
		{
			std::stringstream instr_ss;
			instr_ss << "add_staff Staff_" << i;
			instr_ss << " 3";
			for (int j = 0; j < 6; ++j)
			{
				instr_ss << " " << rand() % 2;
			}
			for (int j = 0; j < 3; ++j)
			{
				instr_ss << " " << rand() % 10; // Random course index
			}
			output << instr_ss.str() << std::endl;
		}
	}
	output.close();
}

bool autotest(std::string long_sequence, std::string short_sequence_1, std::string short_sequence_2, std::string addr, int port)
{
	// 1: Testing big instructions section

	connector Test_Connector(addr, port);
	try
	{
		Test_Connector.execute_instructions(long_sequence);
		Test_Connector.request("clear", false);
	}
	catch (const std::exception& exc)
	{
		std::cout << "Autotest failed with error <" << exc.what() << ">" << std::endl;
		return false;
	}

	connector C_1(addr, port), C_2(addr, port);
	try
	{
		C_1.execute_instructions(short_sequence_1);
		C_1.request("clear", false);
		C_2.execute_instructions(short_sequence_2);
		C_2.request("clear", false);
	}
	catch (const std::exception& exc)
	{
		std::cout << "Autotest failed with error <" << exc.what() << ">" << std::endl;
		return false;
	}
	std::cout << "Autotest passed successfully." << std::endl;
	return true;
}