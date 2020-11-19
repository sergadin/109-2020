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

		List();
		~List();

		void add(T value);
		//void del();
		//void go_next();
		//void go_prev();
		//T get_current();
		//void print() const;
		//void delite ();

		//void operator =(const List &elem);
		//bool operator ==(const List &elem);

};