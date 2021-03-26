#include <iostream>

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
/*
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
*/


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

	void add_first_elem (T value);
        void add_last_elem (T value);

	void change_elem(ListItem *item, T elem);

        void del_first_elem ();
        void del_last_elem ();

        void add_after_elem (T value, ListItem *item);
        void add_before_elem (T value, ListItem *item);

        void del_elem (ListItem *item);
        void swap_elem (ListItem *item, ListItem *elem);

        void get_first();
        void go_next();
        void go_back();
        void print() const;

	list operator = (const list & other);

//	list<T>(T item);
//	list();
//	~list();


//	list(int n);
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


