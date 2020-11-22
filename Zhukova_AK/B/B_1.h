#include <iostream>

template <typename T>

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

	ListItem *next (ListItem *element)
	{
		return element->next;
	}

	ListItem *prev (ListItem *element)
        {
                return element->prev;
        }

public:

	void add_first_elem (T value);
        void add_last_elem (T value);

        void del_first_elem ();
        void del_last_elem ();

        void add_after_elem (T value);
        void add_before_elem (T value);

        void del_elem (ListItem &item);
        void swap_elem (ListItem &item, ListItem &elem);

        void get_first();
        void go_next();
        void go_back();
        void print();

	list();
	~list();

};
