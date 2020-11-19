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
		ListItem (ListItem *prev, ListItem *next, T data);
	};

	ListItem *first;
	ListItem *last;
	ListItem current;

	int size;

public:

	class Iterator
	{
	private:

		ListItem current;
	public:

		Iterator (const Iterator& l);
		~Iterator();

		void go_next();
		void go_back();

		T get_current();

		bool is_last();
		bool is_first();
		bool is_valid();
	};

	Iterator begin();

	void add_elem (T value);
	void del_elem (T value);

	void get_first();
	void go_next();
        void go_back();


	list ();
	~list();

};


class Exception
{
        private:
                int code_;
                std::string message_;
        public:
                Exception(int code, const std::string& message) : code_(code), message_(message) {}
                const std::string& message() const { return message_; }
                int code() const { return code_; }
};
