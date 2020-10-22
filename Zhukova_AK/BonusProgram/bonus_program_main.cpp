#include "bonus_program.h"

int main (void)
{
	try
	{
		BonusProgram a(4, std::string("program"));
		BonusProgram b(4, std::string("program"));
		BonusProgram c(4, std::string("program"));
		BonusProgram d(4, std::string("program"));

		a.Registration(2,100);
		a.Registration(3,100);

		b.Registration(0,1100);
		b.Registration(2,100);

		c.Registration(2,100);
                c.Registration(3,100);
                c.Registration(0,1000);
                c.Registration(2,100);

		printf ("a, b, c:\n");
		a.print();
		b.print();
		c.print();

		printf ("d:\n");
		d = a + b;
		d = d + c;
		d.print();

		if (a < c)
		{
			printf ("a<c\n");
		}
		else
		{
			if (c < a)
			{
				printf ("a>c\n");
			}
			else
			{
				printf ("a и c несравнимы\n");
			}
		}
		printf ("a + b:\n");
		(a + b).print();
	}

	catch (BonusProgramException &ex)
	{
		std::cerr << "Ошибка" << std::endl;
	}

	return 0;
}
