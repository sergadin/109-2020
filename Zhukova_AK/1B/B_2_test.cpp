#include "B_2.hpp"

int main(void)

{

printf ("P11\n");


	list<int> l;

printf ("P12\n");

        l.p = 10;

printf ("P13\n");


//      l.print();

        l.add_first_elem(1);
        l.add_first_elem(2);
        l.add_first_elem(3);


printf ("P14\n");

//      l.get_first();

/*      for (int i=0;i<3;i++)
        {
                l.change_elem(current, i);
                l.go_next();
        }
*/
        l.print();

printf ("P1\n");





	return 0;
}
