#include "Hash.h"

int main()
{
	Hash<double> doub;
	Hash<string> str;
	doub.fill("first.txt");
	str.fill("second.txt");

	cout << doub.get("b")<<endl;
	cout << str.get("c") << endl;
 
	doub.insert("t", 234);
	cout << doub.get("t") << endl;
	return 0;
}