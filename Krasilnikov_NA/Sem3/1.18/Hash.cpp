#include "Hash.h"

int key(string key)
{
	int sum = 0, len = key.length();
	key = key.c_str();
	for (int i = 0; i < len; i++) sum += (int)key[i];
	return sum % 8192;
}
