#include <math.h>
#include <iostream>
#include <cstdio>

using namespace std;

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

		//new_elem->data = NULL;
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
                get_first();
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

		get_first();
        }

        void change_elem(T elem)//меняет значение текущего элемента +
        {
                current->data = elem;
        }

        void del_first_elem ()//удаляет первый элемент +
        {
                first = first->next;
                first->prev = NULL;
	}

        void del_last_elem ()//удаляет последний элемент +
        {
                last = last->prev;
		last->next = NULL;
        }

        void add_after_current (T element)//добавляет элемент после текущего +
        {
        //if next || prev == null  ???
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
                //if next || prev == null  ???
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
//if next || prev == null  ???

		go_back();
		current->next = current->next->next;
		go_next();
		current->prev = current->prev->prev;
        }

        void swap_elem ()//меняет местами текущий и следующий элементы
        {
		T help;
		help = current->data;
		current->data = current->next->data;
		current->next->data = help;
	}

        void get_first()//возвращается в начало списка +
        {
	          current = first;
        }

        void go_next()//переход к следующему элементу +
        {
                current = current->next;
        }

        void go_back()//переход к предыдущему элементу +
        {
                current = current->prev;
        }

        void print() //печатает список +
        {
                get_first();
//проверка, что следующий элемент есть

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


        list operator = (const list & other)// +-
        {
                get_first();

                while (other.current != NULL)
                {

			this->add_last_elem(other.current->data);
			//this->current = other.current;
			//this->next = other.next;
                        //this->data = other.data;
			go_next();
                }
                return *this;


        }

//      list();
//      ~list();

};


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










