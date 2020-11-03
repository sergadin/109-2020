#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Stack
{
	T item;
	Stack<T>* next;
};

class StackListError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		StackListError(int code, const std::string& reason)
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
class StackList
{
	private:
		Stack<T>* vershina;

	public:
		StackList() 
		{ 
		vershina = nullptr; 
		}
		
		void Put(T i)// добавить
		{
			Stack<T>* p;
			p = new Stack<T>;
			p->item = i;
			p->next = vershina;
			vershina = p;
		}

		void Print(const char* o)// вывод стека
		{
			cout << "Stack: " << o << endl;
			if (vershina == nullptr)
			{
				throw StackListError(-1, std::string("empty"));
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

		void Del()// удаление вершины
		{
			if (vershina == nullptr)
			{
				throw StackListError(-5, std::string("empty"));
		        }
			Stack<T>* p;
			T item;
			item = vershina->item;
			p = vershina;
			vershina = vershina->next;
			delete p;
		}

		StackList<T>& operator=(const StackList<T>& L)// копирование
		{
			Stack<T>* p;
			Stack<T>* p1;
			Stack<T>* t;

			vershina = nullptr;
			t = nullptr;

			p = L.vershina;
			while (p != nullptr)
			{
				// 1. Сформировать узел p1
				try {
					// попытка выделить память
					p1 = new Stack<T>;
				}
				catch (bad_alloc e)
				{
					// если память не выделена, то выход
					cout << e.what() << endl;
					return *this;
				}
				p1->item = p->item;
				p1->next = nullptr;

				// 2. pTop = pTop + p2
				if (vershina == nullptr) // создать стек
				{
					vershina = p1;
					t = p1;
				}
				else
				{
					t->next = p1;
					t = t->next;
				}

				// 3. Перейти на следующий элемент
				p = p->next;
			}
			return *this;
		}
};

int main()
{
	try
        {
	StackList<int> S;
	S.Put(8);
	S.Put(5);
	S.Put(10);
	S.Put(7);
	S.Print("S");
	
	StackList<int> S1;
	S1.Put(1);
	S1.Put(2);
	S1.Put(3);
	S1.Print("S1");
	
	StackList<int> S5;
	S5 = S;
	S5.Print("S5");
	
	S.Del();
	S.Print("S");

	StackList<int> L;
	L.Print("L");
	}
	catch(StackListError &err)
        {
                std::cout << err.get_reason() << std::endl;
        }
	return 0;
}
