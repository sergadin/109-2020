#include <iostream>
#include "vclock.h"


using namespace std;
int main()
{
	Vclock q(3,0);

	try
	{
		Vclock q2(3, 1);
		Vclock q3(3, 2);
		Vclock q4(5, 2);
		Vclock q5(3, 2);
		q.local_ev();
		q2.local_ev();
		q.global_ev(q2);
		if(q4 <= q)
			std::cout<< 111111111111112<< endl;
		q4 = q;
  		std::cout<< q4<< endl;
		std::cout<< q2<< endl;
  		return 0;
	}
	catch(MatrError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}
	std::cout << q << endl;

	return 0;


}
