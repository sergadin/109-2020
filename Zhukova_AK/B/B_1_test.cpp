#include "B_1.h"

using namespace std;

int main(void)
{



	list <int> l;

	l.add_first_elem(1);
	l.add_first_elem(1);
	l.add_first_elem(1);

//	l.get_first();

/*	for (int i=0;i<3;i++)
	{
		l.change_elem(current, i);
		l.go_next();
	}
*/
	l.print();

	return 0;

}
