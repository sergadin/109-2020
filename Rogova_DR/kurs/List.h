#include <string>
#include <math.h>
#include <iostream>
#include <cstdio>

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

		ListItem *base_;
		ListItem *current_;
	public:
		class Iterator
		{
			private:
				ListItem *cur_;

				Iterator()
				{
					cur_= new ListItem;
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
				}
				Iterator& operator --()
				{
					cur_ = cur_->bef;
				}
				T get_now()
				{
					return cur_->data;
				}


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
			current_ = p;
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
		void del_all()
		{

			ListItem *elem = base_->next;
			delete base_;
			ListItem *m;
			while (elem != 0)
			{
				m = elem->next_;
				delete elem;
				elem = m;
			}
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
		void print() const
		{
			ListItem * p;
			p = base_->next;
			while (p != nullptr)
			{
				std::cout << p->data << "\t";
				p = p->next;
			}
			std::cout << std::endl;
		}

		List<T> &operator =(const List &elem)
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
};
