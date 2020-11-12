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
		base_.data = nullptr;
		ListItem *current_;
	public:
		class Iterator
		{
			private:
				ListItem *cur_;
				Interator()
				{
					cur_ = new Listitem;
					cur_ = data_.next;
				} 
			public:
				Iterator& operator ++();
				Iterator& operator --();
				bool operator ==(const Iterator &right);

		};

		List();
		~List();

		Iterator begin()
		{
			Iterator i();
			return i;
		}
		void add_after(T new_el)
		{
			ListItem* p;
			p = new ListItem;
			p->data = new_el;
			p->next = current_->next;
			p->bef = current_;
			go_prev();
			current_->next = p;
			go_next();
			go_next();
			current_->bef = p->next;
			current = p;
		}
		void del_el()
		{
			ListItem * prevel;
			go_prev();
			prevel = current_;
			go_next();
			prevel->next = current_->next;
			current_ = prevel;
			delete prevel;

		}
		void go_next()
		{
			current_->next;
                        if(!current_.data)
                        {
                                current_ = base_->next;
                        }
			
		}
		void go_prev()
		{
			current_->bef;
                        if(!current_.data)
                        {
                                current_ = base_->bef;
                        }
		}
		T get_current()
		{
                        if(!current_.data)
                        {
                                current_ = base_->next;
                        }
			return current_->data;
		}
		void print() const;
		{
			ListItem * p;
			p = base_->next;
			while (p != nullptr)
			{
				cout << p->data << "\t";
				p = p->next;
			}
			cout << endl;
		}

		List & List::operator =(const List &elem)
		{
			del_el();

			if(elem.base_->next != nullptr)
			{

			}
			while (p != nullptr)
			{
				p1 = new Stack<T>;
				p1->item = p->item;
				p1->next = nullptr;
				if (vershina == nullptr)
				{
					vershina = p1;
					t = p1;
				}
				else
				{
					t->next = p1;
					t = t->next;
				}
				p = p->next;
			}
			return *this;
		}

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
}
