#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Stack
{
	T item;
	Stack* next;
};

class StackLError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		StackLError(int code, const std::string& reason)
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
class StackL
{
	private:
		Stack<T>* vershina;
	public:
		class Iterator
		{
			private:
				friend class StackL<T>;
				Stack<T>* current_;
			public:
				Iterator()
				{
					current_ = nullptr;
				}

				Iterator& operator=(const Iterator & right)
				{
					current_ = right.current_;
					return *this;
				}

				friend bool operator!=(const Iterator & lev, const Iterator& prav)
				{
					if(lev.current_ != prav.current_)
						return true;
					else
						return false;
				}
				friend Iterator& operator ++(Iterator & i)
				{
					i.current_ = i.current_->next;
					return i;
				}
				friend T & operator*(const Iterator & i)
				{
					return i.current_->item;
				}
		};

		Iterator begin()
		{
			Iterator i;
			i.current_ = vershina;
			return i;
		}

		Iterator end()
		{
			Iterator i;
			i.current_ = vershina;
			while(i.current_ != nullptr)
			{
				i.current_=i.current_->next;
				if(i.current_->next == nullptr)
					break;
			}
			return i;
		}

		StackL() 
		{ 
			vershina = nullptr; 
		}

		~StackL()
		{
			Empty();
		}

		void Put(T i)// добавить
		{
			Stack<T>* p;
			p = new Stack<T>;
			p->item = i;
			p->next = vershina;
			vershina = p;
		}

		void Empty()
		{
			Stack<T>* p;
			Stack<T>* p1;

			p = vershina;

			while (p != nullptr)
			{
				p1 = p;
				p = p->next;
				delete p1;
			}
			vershina = nullptr;
		}

		void Print()// вывод
		{
			if (vershina == nullptr)
			{
				throw StackLError(-1, std::string("empty"));
			}
			else
			{
				Stack<T>* p;
				p = vershina;
				while (p != nullptr)
				{
					cout << p->item << "\t";
					p = p->next;
				}
				cout << endl;
			}
		}

		void Del()// вынуть вершину стека
		{
			if (vershina == nullptr)
			{
				throw StackLError(-5, std::string("empty"));
			}
			Stack<T>* p;
			T item;
			item = vershina->item;
			p = vershina;
			vershina = vershina->next;
			delete p;
		}

		StackL<T>& operator=(const StackL<T>& right)// копирование
		{
			Stack<T>* p;
			Stack<T>* p1;
			Stack<T>* t;
			Empty();
			vershina = nullptr;
			t = nullptr;
			p = right.vershina;
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

		int dlina(StackL<T>& S)
		{
			StackL<T>::Iterator i;
			StackL<T>::Iterator r;
			int l = 1;
			r = S.end();
			for(i = S.begin(); i != r; ++i)
               		{
                        	l = l+1;
                	}
			return l;
		}
};

int main()
{
	try
	{
		StackL<int> S;
		S.Put(8);
		S.Put(5);
		S.Put(10);
		S.Put(7);
		cout << "S"<< endl;
		S.Print();

		StackL<int> S1;
		S1.Put(1);
		S1.Put(2);
		S1.Put(3);
		cout << "S1"<< endl;
		S1.Print();

		StackL<int> S5;
		S5 = S;
		cout << "S5"<< endl;
		S5.Print();

		S.Del();
		cout << "S"<< endl;
		S.Print();

		S.Put(1);
		S.Put(4);
		S.Put(6);
		S.Put(9);
		S.Put(15);
		S.Put(19);
		cout << "S"<< endl;
		S.Print();




		StackL<int>::Iterator i;
		StackL<int>::Iterator i1;
		StackL<int>::Iterator i5;
		StackL<int>::Iterator r;
		int l;
		int k;
		int p;
		int t;
		int m;
		l = S.dlina(S);
		m = l;
		r = S.end();
		for(i = S.begin(); i != r; ++i)
		{
			if ((l == m/2) || (l == (m+1)/2))
				break;
			p = 0;
			i1 = S.begin();
			for(k = 1; k != l; ++k)
			{
				++i1;
			}
			p = *i;
			*i = *i1;
			i5 = i;
			i = S.begin();
			for(t = 1; t != l; ++t)
			{
				++i;
			}
			*i = p;
			i = i5;
			l = l-1;
		}




		cout << "S"<< endl;
		S.Print();
		
		StackL<StackL<int>> E;
		//E.Put(S);
		//E.Put(S1);
		//E.Put(S5);
		//cout << "E"<< endl;
		//E.Print();

		StackL<int> L;
		cout << "L"<< endl;
		L.Print();
	}
	catch(StackLError &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}
