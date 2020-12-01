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
	unsigned char read_buffer[4];
	unsigned char buffer2[100];

	int len = 5;
	
	disk.write("hello.txt", 0, len, bytearray);

	cout << "Now we'll read 4 last bytes of the file hello.txt" << endl;
	disk.read("hello.txt", 1, 4, read_buffer);
	for (int i = 0; i < 4; i++) {
		fprintf(stdout, "%u ", read_buffer[i]);
	}
	cout << endl;

	disk.cp("hello.txt", "hello2.txt");
	cout << disk.wc("hello2.txt") << endl;

	for (int i = 0; i < 9; i++) {
		disk.write("hello2.txt", 5 + i * 5, 5, bytearray);
	}

	try {
		disk.create("New_message.sms");
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	disk.ls();	
	cout << "Length of hello2.txt = " << disk.wc("hello2.txt") << endl;
	disk.printFAT();

	cout << "Now we'll delete 32 bytes of hello2.txt" << endl;
	disk.del("hello2.txt", 32);
	cout << "New length of hello2.txt = " << disk.wc("hello2.txt") << endl;

	disk.read("hello2.txt", 4, disk.wc("hello2.txt") - 4, buffer2);
	cout << "So, let's read hello2.txt since 5th byte:" << endl;
	for (int i = 0; i < disk.wc("hello2.txt") - 4; i++) {
		fprintf(stdout, "%u ", buffer2[i]);
	}
	cout << endl;

	cout << "Now we'll try to delete 100 bytes of hello2.txt" << endl;
	disk.del("hello2.txt", 100);
	cout << "New length of hello2.txt = " << disk.wc("hello2.txt") << endl;
	
	disk.printFAT();
	return 0;
}
