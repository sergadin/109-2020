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

		void Print()// вывод
		{
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

		void Del()// удаление вершины стека
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

		StackList<T>& operator=(const StackList<T>& right)// копирование
		{
			Stack<T>* p;
			Stack<T>* p1;
			Stack<T>* t;
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
	cout << "S"<< endl;
	S.Print();
	
	StackList<int> S1;
	S1.Put(1);
	S1.Put(2);
	S1.Put(3);
	cout << "S1"<< endl;
	S1.Print();
	
	StackList<int> S5;
	S5 = S;
	cout << "S5"<< endl;
	S5.Print();
	
	S.Del();
	cout << "S"<< endl;
	S.Print();

	StackList<int> L;
	cout << "L"<< endl;
	L.Print();
	}
	catch(StackListError &err)
        {
                std::cout << err.get_reason() << std::endl;
        }
	return 0;
}
