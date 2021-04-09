
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
		ListItem<T> *top_;
	public:
		class Iterator
		{
			private:
				friend class List<T>;
				friend class ListItem<T>;
				ListItem<T> *cur_;
				ListItem<T> *b_;
				ListItem<T> *p_;

			public:
				Iterator()
				{
					cur_= nullptr;
					b_ = nullptr;
					p_ = nullptr;
				}
				friend bool operator !=(const Iterator& left, const Iterator right)
				{
					if(left.cur_ != right.cur_)
						return true;
					else
						return false;
				}
				void next_go()
                                {
                                        cur_ = cur_->next;
					if(cur_== p_)
		                        {
                		                cur_ = cur_->bef;
                       			}

                                }
				void bef_go()
                                {
                                        cur_ = cur_->bef;
					if(cur_== b_)
                                        {
                                                cur_ = cur_->next;
                                        }


                                }
				T get_it()
                                {
                                        return cur_->data;
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
			top_ = new ListItem<T>;
			base_->bef = base_;
			base_->next = top_;
			top_->next = top_;
			top_->bef = base_;
			current_ = base_;

		}
		List(const List& A)
		{
			ListItem<T>* p;
                        ListItem<T>* p1;
                        ListItem<T>* b;
			base_ = new ListItem<T>;
			top_ = new ListItem<T>;
			base_->next = top_;
			base_->bef = base_;
			top_ ->bef = base_;
			top_->next = top_;
                        current_ = base_;
                        p = A.base_;
                        p = p->next;
                        while (p != A.top_)
                        {
                                add_after(p->data);
                                p = p->next;
                        }
                        current_ = base_->next;
		}
		~List()
		{
			current_ = base_;		
			del_all();
			delete base_;
			delete top_;

		}
		Iterator begin()
		{
			Iterator i;
			i.cur_ = base_;
			i.b_ = base_;
			i.p_ = top_;
			i.next_go();
			return i;
		}
		Iterator end()
		{
			Iterator i;
			i.cur_ = top_; 
			i.b_ = base_;
			i.p_ = top_;
			return i;
		}
		void add_after(T new_el)
		{
			ListItem<T>* p;
			p = new ListItem<T>;
			p->data = new_el;
			p->next = top_;
			p->bef = top_->bef;
			top_->bef = p;
			current_ = p->bef;
			current_->next = p;
			current_ = p;
		}
		bool is_empty()
		{
			if(base_->next == top_)
				return true;
			else
				return false;
		}
		bool is_end()
		{
			if(current_ == top_)
				return true;
			else
				return false;
		}
		void del_el()
		{
			if(is_empty())
				return;
			if(current_ == base_)
				current_=current_->next;
			if(current_ == top_)
				current_ = current_ ->bef;
			if(current_ == base_)
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
			ListItem<T> *m;
			current_ = base_->next;
			while (current_ != top_)
			{
				m = current_;
				current_ = current_->next;
				delete m;
			}
			base_->next = top_;
			base_->bef = base_;
			top_->bef = base_;
			top_->next = top_;

		}
		void go_next()
		{
			current_ = current_->next;
			if(current_== top_)
			{
				current_ = top_->bef;
			}

		}
		void go_prev()
		{
			current_ = current_->bef;
			if(current_ == base_)
			{
				current_ = base_->next;
			}
		}
		T get_current()
		{
			if(current_ == base_)
				throw ListException(-2, std::string("error"));
			if(current_ == top_)
				throw ListException(-2, std::string("error"));
			return current_->data;
		}
		void print() const
		{
			ListItem<T> * p;
			p = base_->next;
			while (p != top_)
			{
				std::cout << p->data << "\t";
				p = p->next;
			}
			p = nullptr;
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
			while (p != right.top_)
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
			while (p != H.top_)
			{
				out << p->data << "\t";
				p = p->next;
			}
			p = nullptr;
			return out;
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

