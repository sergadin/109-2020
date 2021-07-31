#include <string>
#include <cstdio>
#include <math.h>

using namespace std; 

template <typename T>
class List
{
	private:
		class ListItem
		{
			public:
				T data;
				ListItem *next;
				ListItem *bef;
		};

		ListItem base_;
		ListItem *curent_;
	public:
		class Iterator
		{
			private:
				ListItem *current;
			public:
				Iterator();
				Iterator& operator +();
				Iterator& operator -();
				bool operator ==(const Iterator &right);

		};

		List();
		~List();

		void add_after(T new_el);
		void add_bef(T new_el);
		void del_after();
		void del_before();
		void go_next();
		void go_prev();
		T get_current();
		void print() const;
		void delite ();

		void operator =(const List &elem);
		bool operator ==(const List &elem);

};


class ListException
{
	private:
		int code_;
		string message_;
	public:
		ListException(int code, string message);
		string message() const;
		int code() const;
};
