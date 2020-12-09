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
//        ListItem *current = NULL;

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
		//add_first_elem (new_elem->data);
		//add_last_elem (new_elem->data);

	//	new_elem->data = element;
                new_elem->prev = first;
                new_elem->next = last;
                first = new_elem;
		last = new_elem;
	}

        list(T elem)
        {
                current->data = elem;
                first->data = current->data;
                last->data = current->data;
                first->next = last;
                last->prev = first;
        }

        void add_first_elem (T element) //добавляет элемент в начало списка +++
        {
                ListItem *new_elem = new ListItem;
                new_elem->data = element;
                new_elem->prev = NULL;
                new_elem->next = first;
                first = new_elem;
                get_first();
        }

        void add_last_elem (T element)
        {
                ListItem *new_elem = new ListItem;
                new_elem->data = element;
                new_elem->prev = last;
		new_elem->next = NULL;
                last = new_elem;

	printf ("P25\n");

		get_first();
        }

        void change_elem(ListItem *item, T elem)
        {
                item->data = elem;
        }

        void del_first_elem ();
        //...

        void del_last_elem ()
        {
                last = last->prev;
        }

        void add_after_elem (T element, ListItem *item)
        {
        //if next || prev == null  ???
                ListItem *new_item = new ListItem;
                new_item->prev = *item->prev;
                new_item->data = element;
                new_item->next = *item->data;
                item->prev = *element;
                item->prev->next = *element; //но это не точно
        }

        void add_before_elem (T element, ListItem *item)
        {
                //if next || prev == null  ???
                ListItem *new_item = new ListItem;

                new_item->prev = *item->prev;
                new_item->data = element;
                new_item->next = *item->data;
                item->prev = *element;
                item->prev->next = *element; //но это не точно,$
        }


        void del_elem (ListItem *item)
        {
//if next || prev == null  ???

                item->prev->next = *item->next;
                item->next->prev = *item->prev;

        }

        void swap_elem (ListItem *item, ListItem *elem);
        //...


        void get_first()
        {
//                current->data = first;
  //              current->prev = NULL;
	          current = first;
    //            current->next = first->next;
        }

        void go_next()
        {
                current = current->next;
        }

        void go_back()
        {
                current = current->prev;
        }

        void print()
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


        list operator = (const list & other)
        {
                get_first();

                while (this->next != NULL)
                {
                        this->data = other.data;
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










