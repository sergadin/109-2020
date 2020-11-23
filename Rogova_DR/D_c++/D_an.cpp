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
				friend class List<T>;
				ListItem<T> *cur_;
	
			public:
				Iterator()
                                {
                                        cur_= nullptr;
                                }
				friend Iterator& operator ++(Iterator & i)
				{
					i.cur_ = i.cur_->next;
					return i;
				}
				friend Iterator& operator --(Iterator & i)
				{
					i.cur_ = i.cur_->bef;
					return i;
				}
				friend T& operator*(const Iterator & i)
				{
					return i.cur_->data;
				}
				friend bool operator !=(const Iterator& left, const Iterator right)
				{
					if(left.cur_ != right.cur_)
						return true;
					else
						return false;
				}
				Iterator& operator= (const Iterator & right)
				{
					cur_ = right.cur_;
					return *this;
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
			Iterator i;
			i.cur_ = base_;
			++i;
			return i;
		}
		Iterator end()
		{
			Iterator i;
			i.cur_ = base_;
			++i;
			while(i.cur_ != base_)
			{
				i.cur_ = i.cur_->next;
				if(i.cur_->next == nullptr)
					break;
			}
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
			current_ = p;
		}
		bool is_empty()
		{
			if(base_->next == base_)
				return true;
			else
				return false;
		}
		void del_el()
		{
			if(is_empty())
				return;
			ListItem<T> * prevel;
			prevel = current_;
			current_->bef->next = current_->next;
			current_->next->bef = current_->bef;
			current_ = base_->next;
			delete prevel;

		}
		void del_all()
		{
			if(is_empty())
				return;
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
				throw ListException(-2, std::string("error"));
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
			current_ = base_->next;
			return *this;
		}
		friend std::ostream& operator<<(std::ostream &out, const List<T> &H)
		{
			ListItem<T> * p;
                        p = H.base_->next;
                        while (p != H.base_)
                        {
                                out << p->data << "\t";
                                p = p->next;
                        }
			return out;
		}
		void operator delete[](void* ptr)
		{
			delete ptr;
		
		}



};


int main()
{
	try
	{
		List<int> S;

		S.add_after(10);
		S.add_after(7);
		S.print();
		for(int i = 0; i < 10; i++)
		{
			S.del_el();
		}
		S.print();
		cout << "lalalal"<< endl;
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
		  List<int>::Iterator i;
		  for(i = S1.begin(); i != S1.end(); ++i)
		  {
			  cout<< *i;
		  }
		  List<List<int>> H;
		  S5.add_after(9);
                  S5.add_after(3);
		  H.add_after(S5);
		  H.add_after(S1);
		  std::cout << H<< "!!!!" <<endl;

	}
	catch(ListException &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}

