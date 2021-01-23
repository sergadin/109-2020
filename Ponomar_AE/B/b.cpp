#include <math.h>
#include <iostream>
#include <cstdio>

using namespace std;

class iskl //проверка ошибок
{
	private:
		int code_;
		std::string message_;

	public:
		iskl(int code, std::string message):code_(code), message_(message){}
		std::string message() const{return message_;}
		int code()const{return code_;}
};


template <typename TYPE>
struct list_cell
{
	TYPE data;
	list_cell *next;
	list_cell *previous;
};


template <typename TYPE>
class list
{
	private:

		list_cell<TYPE> *first_; //первая 'вершина' списка
		list_cell<TYPE> *current_; //текущий эл-т
		list_cell<TYPE> *last_; //вторая 'вершина' списка
	public:
		class iterator_cell //итератор для ячейки списка
		{
			private:
				friend class list<TYPE>;
				friend class list_cell<TYPE>;
				list_cell<TYPE> *f_;
				list_cell<TYPE> *curr_;
				list_cell<TYPE> *l_;

			public:
				iterator_cell() 
				{
					f_= nullptr;
					curr_ = nullptr;
					l_ = nullptr;
				}

				friend bool operator !=(const iterator_cell& left, const iterator_cell right)
				{
					if(left.curr_ != right.curr_)
					{
						return true;
					}

					else
					{
						return false;
					}
				}	

				void next_cell() //следующий эл-т
				{
					curr_ = curr_->next;
					if(curr_== l_)
					{
						curr_ = curr_->previous;
					}
				}

				void previous_cell() //предыдущий эл-т
				{
					curr_ = curr_->previous;
					if(curr_== f_)
					{
						curr_ = curr_->next;
					}
				}

				friend TYPE& operator *(const iterator_cell &i) {
                                     return i.curr_->data;
                                }
				iterator_cell& operator= (const iterator_cell & right)
				{
					curr_ = right.curr_;
					return *this;
				}

				void operator ++() {
                                    if (curr_ != nullptr) curr_ = curr_->next;
                                    return;
                                }
		};

		list()
		{
			first_ = new list_cell<TYPE>;
			last_ = new list_cell<TYPE>;

			first_->previous = first_; //'замыкаем' список на концах
			last_->next = last_;

			first_->next = last_;
			last_->previous = first_;

			current_ = first_;

		}

		list(const list& A) //конструктор копирования, который создает список по списку, который подаем
		{
			list_cell<TYPE>* p;
			list_cell<TYPE>* p1;
			list_cell<TYPE>* b;

			first_ = new list_cell<TYPE>;
			last_ = new list_cell<TYPE>;
			first_->next = last_;
			first_->previous = first_;
			last_ ->previous = first_;
			last_->next = last_;
			current_ = first_;

			p = A.first_;
			p = p->next; //вспомогательный элемент, который переходит на первое непустое место

			while (p != A.last_)
			{
				add_after(p->data);
				p = p->next;
			}
			current_ = first_->next;
		}

		~list()
		{
			current_ = first_;		
			delete_all();
			delete first_;
			delete last_;

		}

		iterator_cell begin()
		{
			iterator_cell k;
			k.curr_ = first_;
                        k.f_ = first_;
			k.l_ = last_;
			k.next_cell();
			return k;
		}

		iterator_cell end()
		{
			iterator_cell k;
			k.curr_ = last_; 
			k.f_ = first_;
			k.l_ = last_;
                        
			return k;
		}

		void add_after(TYPE new_element) //добавление элемента 
		{
			list_cell<TYPE>* p;
			p = new list_cell<TYPE>;
			p->data = new_element;
			p->next = last_;
			p->previous = last_->previous;
			last_->previous = p;
			current_ = p->previous;
			current_->next = p;
			current_ = p;
		}

		bool is_empty() //проверяет, пусто или нет
		{
			if(first_->next == last_)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool is_end() //проверяет, где current (на последнем или нет)
		{
			if(current_ == last_)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void delete_element()
		{
			if(is_empty())
				return;
			if(current_ == first_)
				current_ = current_->next;
			if(current_ == last_)
				current_ = current_->previous;
			if(current_ == first_)
				return;

			list_cell<TYPE> * previous_el;
			previous_el = current_;
			current_->previous->next = current_->next;
			current_->next->previous = current_->previous;
			current_ = first_->next;
			delete previous_el;

		}
		void delete_all() //удаляет все кроме начала и конца
		{
			if(is_empty())
				return;
			list_cell<TYPE> *c;
			current_ = first_->next;

			while (current_ != last_)
			{
				c = current_;
				current_ = current_->next;
				delete c;
			}

			first_->next = last_;
			first_->previous = first_;
			last_->previous = first_;
			last_->next = last_;

		}

		void go_next()
		{
			current_ = current_->next;
			if(current_== last_)
			{
				current_ = last_->previous;
			}

		}

		void go_previous()
		{
			current_ = current_->previous;

			if(current_ == first_)
			{
				current_ = first_->next;
			}
		}
		TYPE get_current()
		{
			if(current_ == first_)
				throw iskl(-2, std::string("ERROR"));
			if(current_ == last_)
				throw iskl(-2, std::string("ERROR"));
			return current_->data;
		}

		void print() const
		{
			list_cell<TYPE> * p;
			p = first_->next;
			while (p != last_)
			{
				std::cout << p->data << "\t";
				p = p->next;
			}
			p = nullptr;
			std::cout << std::endl;
		}

		list<TYPE>& operator=(const list<TYPE>& right)//
		{
			list_cell<TYPE>* p;
			list_cell<TYPE>* p1;
			list_cell<TYPE>* b;
			delete_all();
			current_ = first_;
			p = right.first_;
			p = p->next;

			while (p != right.last_)
			{
				add_after(p->data); 
				p = p->next;
			}

			current_ = first_->next;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream &out, const list<TYPE> &H)//перегрузка оператора вывода
		{
			list_cell<TYPE> * p;
			p = H.first_->next;
			while (p != H.last_)
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
		list<char> spisok1;
		spisok1.add_after('+');
		spisok1.add_after(',');
		spisok1.add_after('p');
		spisok1.add_after('l');
		spisok1.add_after('e');
		spisok1.add_after('a');
		spisok1.add_after('s');
		spisok1.add_after('e');
		cout << "spisok1"<< endl;
		spisok1.print();

		list<int> spisok2;
		spisok2.add_after(1);
		spisok2.add_after(2);
		spisok2.add_after(345);
		cout << "spisok2"<< endl;
		spisok2.print();

		list<int> spisok3;
                cout << "spisok3 (empty)"<< endl;
                spisok3.print();

		list<char> spisok4;
		spisok4 = spisok1;
		cout << "spisok4 (=spisok1)"<< endl;
		spisok4.print();

                list<int>::iterator_cell i;
                
		cout << "iterator" << endl;
                for(i = spisok2.begin(); i != spisok2.end(); ++i) {
                    cout<< ++(*i) << ' ';
		} cout << endl;
               
		for(i = spisok2.begin(); i != spisok2.end(); ++i) {
			if (*i!=1) *i = 10;
		        cout << *i << ' ';
	        } cout << endl;
		
	}
	catch(iskl &exc)
	{
		std::cout << "ERROR : " << exc.message() << std::endl;
	}
	return 0;
}

