#include "matrix.h"

int main (void)
{
        try
        {
                Matrix m1(2, 3);
		Matrix m2(2, 3);
		Matrix m3(2, 3);

//		printf ("m1:\n");
//		m1.print();
//		printf ("m2:\n");
//		m2.print();
//		printf ("m3:\n");
//		m3.print();

                m1.registration(0, 0, 1);
		m1.registration(1, 0, 15);
		m1.registration(0, 1, 1);

                printf ("m1:\n");
                m1.print();

		m2 = m1;
		m2.registration(1, 2, 5);
		m2.registration(0, 0, 8);

                printf ("m2:\n");
                m2.print();

		m3 = m2 + m1;

		printf ("m3:\n");
                m3.print();

//		printf ("m3: %d %d\n", m3.GetElement(1, 0), m3.GetElement(1, 1));

		Submatrix m4(&m3, 2, 2, 0, 0);

		printf ("m4:\n");
		printf ("%d %d\n", m4.Get_Element(0, 0), m4.Get_Element(0, 1));
		printf ("%d %d\n", m4.Get_Element(1, 0), m4.Get_Element(1, 1));
        }

        catch (Exception &ex)
        {
                std::cerr << "Ошибка" << std::endl;
        }

        return 0;
}
