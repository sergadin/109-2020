#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;
#define Max(a, b) ((a)>(b) ? (a) : (b))
#define Min(a, b) ((a)<(b) ? (a) : (b))
template <typename T >
class List
{
	private:
		class ListItem
		{
			public:
			T data;
			ListItem *next;
		};
	ListItem base_;
	ListItem last_;
	public:
		class Iterator
		{
			private:
				ListItem *current;
			public:
				Iterator();
				~Iterator();
				//Iterator& operator +();
				//Iterator& operator -();
				//bool operator ==(const Iterator &right);

		};

		List()
		{
			base_.data = NULL;
			base_.next = &base_;
		}

		~List();

		void add(T value)
		{
			if(base_.data == NULL)
			{
				base_.data = value;
				last_ = base_;
				return;
			}
			ListItem *new_element = new ListItem;
			new_element.data = value;
			new_element.next = last_.next;
			last_.next = &new_element;
			last_ = new_element;
		}
		//void del();
		//void go_next();
		//void go_prev();
		//T get_current();
		//void print() const;
		//void delite ();

		//void operator =(const List &elem);
		//bool operator ==(const List &elem);

};