#include "B_2.hpp"

int main(void)

{
        try
        {

		list<int> l(3), m(468);

//        l.p = 10;
		printf ("Создали список l:\n");
        	l.print();

        	l.add_first_elem(1);
        	l.add_first_elem(2);
        	l.add_last_elem(4);
        	l.add_last_elem(6);
        	l.add_last_elem(5);

		printf ("Добавили элементы в список l:\n");
        	l.print();

//printf ("P1\n");

		l.get_first();
		l.go_next();
		l.go_next();
		l.change_elem(45);

		printf ("Изменили элемент в l:\n");
		l.print();

		l.get_first();
        	l.go_next();
        	l.go_next();
		l.add_after_current(87);
		l.add_before_current(289);
//l.del_first_elem();
		printf ("Ещё добавили элементы в l:\n");
		l.print();

		m.add_first_elem(872);
		m = l;

		printf("Создали список m=l:\n");
		m.print();

		l.add_first_elem(-75);
        	l.get_first();
        	l.go_next();
        	l.go_next();
		l.del_current_elem();
		printf ("Добавили 1 элемент и удалили в l:\n");
		l.print();

		l.get_first();
        	l.go_next();
        	l.go_next();
		l.go_next();
		l.swap_elem();
		printf ("Поменяли местами элементы из l:\n");
		l.print();

		m = m + l;
		printf ("Приписали к списку m список l:\n");
        	m.print();

		printf ("В списке l %d элементов, в m - %d\n\n", l.number_of_items(), m.number_of_items());

		m.sort_list();
		printf ("Отсортировали список m:\n");
		m.print();

		printf ("Программа завершила свою работу без ошибок!\n");
	}

        catch (Exception &ex)
        {
                std::cerr << "Ошибка" << std::endl;
        }

	return 0;
}
