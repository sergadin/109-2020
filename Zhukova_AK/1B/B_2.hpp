#include <math.h>
#include <iostream>
#include <cstdio>

using namespace std;


class Exception
{
        private:
                int code_;
                std::string message_;
        public:
                Exception(int code, const std::string& message) : code_(code), message_(message){}
                const std::string& message() const { return message_; }
                int code() const { return code_; }
};


template <class T>
class list
{
private:
        class ListItem
        {
        public:
                T data;
                ListItem *next;
                ListItem *prev;
        };

	ListItem *current;

        ListItem *first = NULL;
        ListItem *last = NULL;

        ListItem *next (ListItem *element)
        {
                return element->next;
        }

        ListItem *prev (ListItem *element)
        {
                return element->prev;
        }

public:
//        int p;
	list()
	{
		ListItem *new_elem = new ListItem;

		new_elem = NULL;
                new_elem->prev = first;
                new_elem->next = last;
                first = new_elem;
		last = new_elem;
	}

        list(T elem)
        {
                ListItem *new_elem = new ListItem;
                new_elem->data = elem;
                new_elem->prev = first;
                new_elem->next = last;
                first = new_elem;
                last = new_elem;
        }

        void add_first_elem (T element) //добавляет элемент в начало списка +
        {
                ListItem *new_elem = new ListItem;
                new_elem->data = element;
                new_elem->prev = NULL;
                new_elem->next = first;
		first->prev = new_elem;
                first = new_elem;
        }

        void add_last_elem (T element)//добавляет элемент в конец списка +
        {
                ListItem *new_elem = new ListItem;
                new_elem->data = element;
                new_elem->prev = last;
		new_elem->next = NULL;
		last->next = new_elem;
                last = new_elem;

	//printf ("P25\n");
        }

        void change_elem(T elem)//меняет значение текущего элемента +
        {
                current->data = elem;
        }

        void del_first_elem ()//удаляет первый элемент +
        {
                if (first != NULL)
                {
			first = first->next;
			first->prev = NULL;
		}
	}

        void del_last_elem ()//удаляет последний элемент +
        {
		if (last != NULL)
		{
                	last = last->prev;
			last->next = NULL;
		}
        }

        void clear_list ()//удаляет список+
        {
		if (first != NULL)
		{
                	get_first();
			while (first->next != NULL)
                	{
				del_first_elem();
			}
			first = NULL;
		}
        }

        void add_after_current (T element)//добавляет элемент после текущего, но не после последнего +
        {
		if (current == NULL || current->next == NULL)
		{
			throw Exception (1, std::string("Нельзя вставить элемент после текущего\n"));
		}

                ListItem *new_item = new ListItem;

                new_item->prev = current;
                new_item->data = element;
                new_item->next = current->next;

		go_next();
                current->prev = new_item;
		go_back();
		go_back();
                current->next = new_item;
        }

        void add_before_current (T element)//добавляет элемент перед текущим +
        {
                if (current == NULL || current->prev == NULL)
                {
                        throw Exception (2, std::string("Нельзя вставить элемент перед текущим\n"));
                }


                ListItem *new_item = new ListItem;

                new_item->prev = current->prev;
                new_item->data = element;
                new_item->next = current;

                current->prev = new_item;
                go_back();
                go_back();
                current->next = new_item;
        }

        void del_current_elem ()//удаляет текущий элемент +
        {
                if (current == NULL || current->next == NULL || current->prev == NULL)
                {
                        throw Exception (3, std::string("Нет текущего\n"));
                }

		go_back();
		current->next = current->next->next;
		go_next();
		current->prev = current->prev->prev;
        }

        void swap_elem ()//меняет местами текущий и следующий элементы +
        {
                if (current == NULL || current->next == NULL)
                {
                        throw Exception (4, std::string("Нет текущего или следующего\n"));
                }

		T help;
		help = current->data;
		current->data = current->next->data;
		current->next->data = help;
	}

        void get_first()//возвращается в начало списка +
        {
	          current = first;
        }

        void get_last()//возвращается в конец списка +
        {
                  current = last;
        }

        void go_next()//переход к следующему элементу +
        {

                if (current == NULL)
                {
                        throw Exception (5, std::string("Нет следующего\n"));
                }

                current = current->next;
        }

        void go_back()//переход к предыдущему элементу +
        {
                if (current == NULL)
                {
                        throw Exception (6, std::string("Нет предыдущего\n"));
                }

                current = current->prev;
        }

        void print() //печатает список +
        {
                get_first();

		if (current == NULL)
		{
			printf ("Список пуст\n");
		}
		else
		{
                	while (current != NULL)
                	{
                        	cout << current->data << "\t";
				printf ("\n");
                	        go_next();
                	}
		}
		cout << endl;
        }

	int number_of_items ()// количество элементов в списке +
	{
		int n = 0;

		get_first();
		while (current != NULL)
                {
			n = n + 1;
			go_next();
		}

		return n;
	}

	void sort_list ()//сортировка элементов списка +
	{
		int n, i, j;
		n = number_of_items ();

                if (n == 0)
                {
                        throw Exception (7, std::string("Список пуст\n"));
                }

		for (i=0; i<n-1; i++)
		{
			get_first();

			for (j=1; j<n; j++)
			{
				if (current->data > current->next->data)
				{
					swap_elem();
				}
				go_next();
			}
		}
	}

        list operator = (const list & other)// +
        {
		this->clear_list();
		ListItem *current_;
		current_ = other.first;
                ListItem *new_elem = new ListItem;
                new_elem->data = current_->data;
                new_elem->prev = other.first;
                new_elem->next = other.last;
                this->first = new_elem;
                this->last = new_elem;
//printf("first=%d\n", new_elem->data);
                while (current_->next != NULL)
               	{
			current_ = current_->next;
			this->add_last_elem (current_->data);
//			current_ = current_->next;
                }
                return *this;
        }

	list operator + ( list & other)
	{

		ListItem *current_;

                current_ = other.first;

		while (current_->next != NULL)
                {
			this->add_last_elem (current_->data);
			current_ = current_->next;
		}
		return *this;
	}

	~list()
	{
		clear_list();
	}
};

