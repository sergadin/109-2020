#include <math.h>
#include <iostream>
#include <cstdio>

class MyExceptions //класс для ошибочек
{
	private:
		int code_;
		std::string message_;

	public:
		MyExceptions(int code, const std::string& message)
		{
			code_ = code;
			message_ = message;
		}
		const std::string& get_reason() const
		{
			return message_;
		}
};

template <typename T>
struct ListItem //это наши элементы списка
{
	T data;
	ListItem *next;
	ListItem *prev;
};

template <typename T>
class List //наш основной класс
{
	private:
		ListItem <T> *root_; //тут у нас есть указатель на "корень" нашего списка
		ListItem <T> *current_; //и указатель на текущий элемент

	public:
		class Iterator //класс итератор
		{
			private:
				friend class List<T>;
				friend class ListItem<T>;
				ListItem<T> *cur_;

			public:
				Iterator() //просто конструктор
				{
					cur_ = nullptr;
				}
				friend bool operator !=(const Iterator& left, const Iterator& right) //оператор неравенства
				{
					if(left.cur_ != right.cur_)
						return true;
					else
						return false;
				}
				void iter_forward(Iterator& i) //шаг итератора вперёд
				{
					i.cur_ = i.cur_->next;
				}
				void iter_backward(Iterator& i) //шаг итератора назад
				{
					i.cur_ = i.cur_->prev;
				}
				T get_current(const Iterator& i) //получить текущее значение
				{
					return i.cur_->data;
				}
				Iterator& operator =(const Iterator& right) //оператор равенства
				{
					cur_ = right.cur_;
					return *this;
				}
		};

		List() //просто конструктор
		{
			root_ = new ListItem<T>;
			root_->prev = root_;
			root_->next = root_;
			current_ = root_;
		}
		List(const List& A) //конструктор с уже существущего образца
		{
			ListItem<T>* x;
			
			root_ = new ListItem<T>;
			root_->next = root_;
			root_->prev = root_;
			current_ = root_;
			x = A.root_;
			x = x->next;

			while(x != A.root_)
			{
				add_elem(x->data);
				x = x->next;
			}

			current_ = root_->next;
			x = nullptr;
		}
		~List() //деструктор
		{
			current_ = root_;
			clean();
			delete root_;
		}
		Iterator start() //итератор на начальную позицию
		{
			Iterator i;
			i.cur_ = root_;
			i.iter_forward(i);
			return i;
		}
		Iterator finish() //итератор на конечную позицию
		{
			Iterator i;
			i.cur_ = root_;
			i.iter_forward(i);
			while(i.cur != root_)
			{
				i.cur_ = i.cur_->next;
				if(i.cur_->next == nullptr)
					break;
			}
			return i;
		}
		void add_elem(T new_el) //добавить элементик на следующую позицию
		{
			ListItem<T>* x;
			x = new ListItem<T>;
			x->data = new_el;
			x->next = root_;
			x->prev = root_->prev;
			current_ = x->prev;
			current_->next = x;
			root_->prev = x;
			current_ = x;
		}
		bool is_empty() //проверить на пустоту
		{
			if(root_->next == root_)
				return true;
			else
				return false;
		}
		void delete_elem() //удалить элементик
		{
			if(is_empty())
				return;
			if(current_ == root_)
				current_ = current_->next;
			if(current_ == root_)
				return;
			ListItem<T>* prev_elem;
			prev_elem = current_;
			current_->prev->next = current_->next;
			current_->next->prev = current_->prev;
			current_ = root_->next;
			delete prev_elem;
		}
		void clean() //очистить списочек
		{
			if(is_empty())
				return;
			ListItem<T>* x;
			current_ = root_->next;
			while(current_ != root_)
			{
				x = current_;
				current_ = current_->next;
				delete x;
			}
			root_->next = root_;
			root_->prev = root_;
		}
		void go_next() //переход к следующему
		{
			current_ = current_->next;
			if(current_ == root_)
			{
				current_ = root_->next;
			}
		}
		void go_prev() //переход к предыдущему
		{
			current_ = current_->prev;
			if(current_ == root_)
			{
				current_ = root_->prev;
			}
		}
		T get_current() //вытащить наш текущий элемент
		{
			if(current_ == root_)
				throw MyExceptions(-1, std::string("you tried to get root"));
			else
				return current_->data;
		}
		void print() const //печать нашего списочка
		{
			ListItem<T>* x;
			x = root_->next;
			while(x != root_)
			{
				std::cout << x->data << "\t";
				x = x->next;
			}
			std::cout << std::endl;
		}
		List<T>& operator =(const List<T>& right) //оператор равно
		{
			ListItem<T>* x;
			clean();
			current_ = root_;
			x = right.root_;
			x = x->next;

			while(x != right.root_)
			{
				add_elem(x->data);
				x = x->next;
			}

			current_ = root_->next;
			x = nullptr;
			return *this;
		}
		friend std::ostream& operator<<(std::ostream &out, const List<T> &A) //оператор вывода
		{
			ListItem<T>* x;
			x = A.root_->next;
			while(x != A.root_)
			{
				out << x->data << "\t";
				x = x->next;
			}
			x = nullptr;
			return out;	
		}
};

int main()
{
	try
	{
		List<int> A;
		A.add_elem(7);
		A.add_elem(8);
		std::cout<<"List A:";
		A.print();
		A.clean();
		std::cout<<"List A:";
		A.print();
		A.add_elem(15);
		A.delete_elem();
		A.add_elem(10);
		A.add_elem(11);
		List<int> B;
		B = A;
		std::cout<<"List B:";
		B.print();
		List<List<int>> C;
		C.add_elem(A);
		C.add_elem(B);
		std::cout<<"List C:";
		C.print();
	}
	catch(MyExceptions &err)
	{
		std::cout<<err.get_reason()<<std::endl;
	}

	return 0;
}
