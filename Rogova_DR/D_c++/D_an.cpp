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
					return cur_;
				}
				Iterator& operator --()
				{
					cur_ = cur_->bef;
					return cur_;
				}
				T get_now()
				{
					return cur_->data;
				}


		};

		List()
		{
			base_ = nullptr;
		}
		Iterator begin()
		{
			Iterator i();
			return i;
		}
		void add_after(T new_el)
		{
			cout<<"lals";
			ListItem<T>* p;
			cout<<"krrrr";
			p = new ListItem<T>;
			cout<<"lalala";
			p->data = new_el;
			p->next = base_;
			p->bef = base_->bef;
			current_ = p->bef;
			current_->next = p;
			base_->bef = p;
		}
		void del_el()
		{
			ListItem<T> * prevel;
			go_prev();
			prevel = current_;
			go_next();
			prevel->next = current_->next;
			current_ = prevel;
			delete prevel;

		}
		void del_all()
		{

			ListItem<T> *elem = base_->next;
			delete base_;
			ListItem<T> *m;
			while (elem != 0)
			{
				m = elem->next;
				delete elem;
				elem = m;
			}
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
			if(!current_.data)
			{
				current_ = base_->next;
			}
			return current_->data;
		}
		void print() const
		{
			ListItem<T> * p;
			p = base_->next;
			while (p != nullptr)
			{
				std::cout << p->data << "\t";
				p = p->next;
			}
			std::cout << std::endl;
		}

		/*List<T> &operator =(const List &elem)
		  {
		  if (base_ != elem.base_)
		  {
		  del_all();
		  elem.current_= elem.base_;
		  current_ = base_;
		  add_after(elem.current_->data);
		  elem.go_next();
		  go_next();
		  while (elem.current_ != 0)
		  {
		  add_after(elem.current_->data);
		  elem.go_next;
		  go_next;
		  }

		  }
		  return *this;
		  }*/

		List<T>& operator=(const List<T>& right)// копирование
		{
			ListItem<T>* p;
			ListItem<T>* p1;
			ListItem<T>* b;
			b = right.base_;
			p = right.base_;
			p = p->next;
			while (p != b)
			{
				p1 = new ListItem<T>;
				p1->data = p->data;
				p1->next = nullptr;
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
		cout << "S"<< endl;
		//S.print();

		/*List<int> S1;
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
		  L.print();*/
	}
	catch(ListException &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}

