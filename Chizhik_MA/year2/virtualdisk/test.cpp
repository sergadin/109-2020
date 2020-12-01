#include "disk.hpp"
using namespace std;

int main(void) {
	VirtualDisk disk(1 << 6, 5);
	disk.create("1");
	disk.create("hello.txt");

	try {
		disk.create("bye.txt");
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	disk.mv("1", "2");
	disk.ls();
	disk.rm("2");

	try {
		disk.rm("file_that_does_not_exist.pdf");
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	unsigned char bytearray[] = {245, 34, 87, 98, 123};
	int len = 5;
	
	disk.write("hello.txt", 0, len, bytearray);

	unsigned char read_buffer[4];
	disk.read("hello.txt", 1, 4, read_buffer);
	for (int i = 0; i < 4; i++) {
		fprintf(stdout, "%u ", read_buffer[i]);
	}
	cout << endl;

	disk.cp("hello.txt", "hello2.txt");
	cout << "SUCCESS" << endl;
	try {
		for (int i = 0; i < 10; i++) {
			disk.write("hello2.txt", 5 + i * 5, 5, bytearray);
		}
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	disk.ls();
	disk.del("hello2.txt", 32);
	cout << disk.wc("hello2.txt") << endl;
	disk.printFAT();
	return 0;
}
