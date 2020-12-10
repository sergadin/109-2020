#include "disk.hpp"
using namespace std;

int main(void) {
	VirtualDisk disk;
	VirtualDisk::File *one, *hello, *hello2, *bye, *goodbye, *five, *root;
	VirtualDisk::File *project, *pr_copy, *index, *styles, *script, *pictures, *pictures2, *hat, *hat2, *cat;

	one = disk.create("1");
	hello = disk.create("hello.txt");
	bye = disk.create("/bye", 1);
	goodbye = disk.create("bye/goodbye/", 1);
	five = disk.create("bye/goodbye/5.txt");

	root = disk.open("/");

	cout << "Directory \"bye\":" << endl;
	bye->ls();
	
	try {
		one->ls();
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	one->mv("2");

	cout << "Root:" << endl;
	root->ls();

	one->rm();

	try {
		one->mv("1");
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	project = disk.create("bye/goodbye/project", 1);
	index = disk.create("bye/goodbye/project/index.php");
	styles = disk.create("bye/goodbye/project/main.css");
	script = disk.create("bye/goodbye/project/script.js");

	pictures = disk.create("bye/goodbye/project/pictures/", 1);
	pictures2 = disk.create("bye/goodbye/project/pictures2", 1);

	hat = disk.create("bye/goodbye/project/pictures/hat.jpg");
	hat2 = disk.create("bye/goodbye/project/pictures/hat.png");

	cat = disk.create("bye/goodbye/project/pictures2/cat.webp");

	//disk.printFAT(16);
	root->ls();

	pr_copy = disk.cp(project, "backup");
	try {
		pr_copy->ls();
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
		cout << pr_copy->wc() << endl;
	}	

	unsigned char bytearray[] = {245, 34, 87, 98, 123};	
	unsigned char read_buffer[4];
	unsigned char buffer2[100];

	try {
		pr_copy->read(0, 64, buffer2);
	} catch (VirtualDiskException &e) {
		cerr << e << endl;
	}

	int len = 5;
	
	hello->write(0, len, bytearray);

	cout << "Now we'll read 4 last bytes of the file hello.txt" << endl;
	hello->read(1, 4, read_buffer);
	for (int i = 0; i < 4; i++) {
		fprintf(stdout, "%u ", read_buffer[i]);
	}
	cout << endl;

	hello2 = disk.cp(hello, "hello2.txt");
	cout << hello->wc() << endl;

	for (int i = 0; i < 9; i++) {
		hello2->write(5 + i * 5, 5, bytearray);
	}

	try {
		disk.create("New_message.sms");
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}

	cout << "Root now:" << endl;
	root->ls();

	cout << "Length of hello2.txt = " << hello2->wc() << endl;
	//disk.printFAT(32);
	cout << "Now we'll delete 32 bytes of hello2.txt" << endl;
	hello2->del(32);
	cout << "New length of hello2.txt = " << hello2->wc() << endl;

	hello2->read(4, hello2->wc() - 4, buffer2);
	cout << "So, let's read hello2.txt since 5th byte:" << endl;
	for (int i = 0; i < hello2->wc() - 4; i++) {
		fprintf(stdout, "%u ", buffer2[i]);
	}
	cout << endl;

	hello2->mv("bye/hello3");

	VirtualDisk::File *new_python_script = disk.cp(hello2, "bye/goodbye/wonder.py");
	delete new_python_script;

	try {
		disk.cp(hello2, "goodbye/wonder.py");
	} catch (VirtualDiskException &e) {
		cerr << e << endl;
	}

	root->ls();

	cout << "Now we'll try to delete 100 bytes of hello2.txt" << endl;
	hello2->del(100);
	cout << "New length of hello2.txt = " << hello2->wc() << endl;

	try {
		hello->read(UINT_MAX / 2 + 187, UINT_MAX - 5, buffer2);
	} catch (VirtualDiskException& e) {
		cerr << e << endl;
	}
	
	//disk.printFAT(32);

	delete hello;
	delete hello2;
	delete bye;
	delete one;
	delete goodbye;
	delete five;
	delete root;

	delete project;
	delete pr_copy;
	delete index;
	delete styles;
	delete script;
	delete pictures;
	delete pictures2;
	delete hat;
	delete hat2;

	delete cat;
	return 0;
}
