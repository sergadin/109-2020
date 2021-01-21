/*

#include <iostream>
#include <cstdio>


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

        ListItem *first = NULL;
        ListItem *last = NULL;
        ListItem *current = NULL;

        ListItem (int n)
        {
                for (int i=0;i<n;i++)
                {
                        ListItem *current = new ListItem;
                        current->next = NULL;
                        current->prev = NULL;
                        current->data = NULL;

                        go_next();
                }
        }



        ListItem *next (ListItem *element)
        {
                return element->next;
        }

        ListItem *prev (ListItem *element)
        {
                return element->prev;
        }

public:

        int p;

        void add_first_elem (T element)
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
        	new_elem ->data = element;
        	new_elem ->prev = last;
        	last = new_elem;
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
        	ListItem *current = new ListItem;
        	current->prev = NULL;
//        current->data = first;
        	current->next = first->next;
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
        	ListItem *elem;
	        get_first();
//проверка, что следующий элемент есть
/*
	        if (current->data == NULL)
  	        {
  	              printf ("Список пуст\n");
	        }
	        else
	        {

                        while (current->next != NULL)
  	                {
	                        printf ("%t\n", current->data);
	                        go_next();
	                }
 //	        }
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


//      list<T>(T item);
//      list();
//      ~list();


//      list(int n);
};
*/

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


//#include "B_1.cpp"


