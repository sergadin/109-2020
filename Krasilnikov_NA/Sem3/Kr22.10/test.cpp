#include "matrix.h"

int main()
{
	try
	{
		Matrix First(1,1);
		cout << First << endl;
		Matrix Second(4,5);
		cout << Second << endl;
		Second.ChangeElem(1,2,4);
		cout << Second << endl;
		First = Second;
		cout << First << endl;
		Matrix Third(1,1);
		cout << Third << endl;
		Third = First + Second;
		cout << Third << endl;
		sub Fourth(&Third, 0, 1, 2, 2);
		cout << Fourth.GetElem(0,0) << " " << Fourth.GetElem(0,1) << endl;  
		cout << Fourth.GetElem(1,0) << " " << Fourth.GetElem(1,1) << endl;  
	}
	catch(Error &ec)
	{
		std::cout<< "Error" << ec.reason() << std::endl;
	}
	return 0;
}
