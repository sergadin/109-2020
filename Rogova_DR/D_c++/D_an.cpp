#include <string>
#include <math.h>
#include <iostream>
#include <cstdio>

using namespace std; 
class ListException
{
		private:
			int code_;
			std::string reason_;
		public:
			ListException(int code, const std::string& reason)
			{
				code_ = code;
				reason_ = reason;
			}

			const std::string& get_reason() const
			{
				return reason_;
			}

};

template <typename T>
struct ListItem
                {
                                T data;
                                ListItem *next;
                                ListItem *bef;
		};


template <typename T>
class List
{
	private:

		ListItem<T> *base_;
		ListItem<T> *current_;
	public:
		class Iterator
		{
			private:
				ListItem<T> *cur_;

				Iterator()
				{
					cur_= new ListItem<T>;
					current_ = base_;
					current_.go_next();
					cur_->data = current_->data;
					cur_->next = current_ ->next;
					cur_->bef = current_->bef;
				}
				~Iterator()
				{
					delete cur_;
				}	
			public:
				Iterator& operator ++()
				{
					cur_ = cur_->next;
					return this;
				}
				Iterator& operator --()
				{
					cur_ = cur_->bef;
					return this;
				}
				T get_now()
				{
					return cur_->data;
				}


		};

		List()
		{
			base_ = new ListItem<T>;
			base_->bef = base_;
			base_->next = base_;
			current_ = base_;

		}
		~List()
		{
			current_ = base_;		
			del_all();
			delete base_;
			
		}
		Iterator begin()
		{
			Iterator i();
			return i;
		}
		void add_after(T new_el)
		{
			ListItem<T>* p;
			p = new ListItem<T>;
			p->data = new_el;
			p->next = base_;
			p->bef = base_->bef;
			current_ = p->bef;
			current_->next = p;
			base_->bef = p;
		}
		void del_el()
		{
			if(current_ == base_)
				return;
			ListItem<T> * prevel;
			prevel = current_;
			current_->bef->next = current_->next;
			current_->next->bef = current_->bef;
			current_ = base_;

		}
		void del_all()
		{

			ListItem<T> *elem = base_->next;
			ListItem<T> *m;
			current_ = base_;
			while (elem != base_)
			{
				m = elem;
				elem = elem -> next;
				delete m;
			}
			base_->next = base_;
			base_->bef = base_;

		}
		void go_next()
		{
			current_ = current_->next;
			if(current_== base_)
			{
				current_ = base_->next;
			}

		}
		void go_prev()
		{
			current_ = current_->bef;
			if(current_ == base_)
			{
				current_ = base_->bef;
			}
		}
		T get_current()
		{
			if(current_ == base_)
			{
				current_ = base_->next;
			}
			return current_->data;
		}
		void print() const
		{
			ListItem<T> * p;
			p = base_->next;
			while (p != base_)
			{
				std::cout << p->data << "\t";
				p = p->next;
			}
			std::cout << std::endl;
		}

		List<T>& operator=(const List<T>& right)//
		{
			ListItem<T>* p;
			ListItem<T>* p1;
			ListItem<T>* b;
			del_all();
			current_ = base_;
			p = right.base_;
			p = p->next;
			while (p != right.base_)
			{
				add_after(p->data); 
				p = p->next;
			}
			return *this;
		}


};


int main()
{
	try
	{
		List<int> S;

		S.add_after(10);
		S.add_after(7);
		int i = S.get_current();

		cout<< i<<endl;
		S.del_all();
		S.print();

		cout << "S"<< endl;

	         List<int> S1;
		  S1.add_after(2);
		  S1.add_after(3);
		  cout << "S1"<< endl;
		  S1.print();

		  List<int> S5;
		  S5 = S;
		  cout << "S5"<< endl;
		  S5.print();

		  S.del_all();
		  cout << "S"<< endl;
		  S.print();

		  List<int> L;
		  cout << "L"<< endl;
		  L.print();
	}
	catch(ListException &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}

