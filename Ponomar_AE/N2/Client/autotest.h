#ifndef AUTOTEST
#define AUTOTEST

#include "connector.h"
#include <ctime>
#include <random>

bool autotest(std::string long_sequence, std::string short_sequence_1, std::string short_sequence_2, std::string addr, int port);

void gen_instructions(std::string output_file, int instructions_number);

#endif//AUTOTEST
