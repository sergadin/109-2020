#include <iostream>
#include <string>

using namespace std; 
class CLASSERROR 
{
	int code_;
	string reason_;
public:
	CLASSERROR(int code, const string& reason)
	{
		code_ = code;
		reason_ = reason;
	}
	const string& get_reason() const
	{
		return reason_;
	}
};

template <typename T>
struct node
{
	T data;
	node *next;
	node *prev;
};

template <typename T>
class BiCircleList
{
	node<T> *base = nullptr;
	node<T> *current = nullptr;
public:
	BiCircleList()
	{
		base = new node<T>;
		base->prev = base;
		base->next = base;
		current = base;
	}
	~BiCircleList()
	{	
		clean();
		delete base;
	}

	class Iterator
	{
	private:
			node<T> *cur = nullptr;
	public:
		Iterator() = default;
		void set(node<T> *new_node)
		{
			cur = new_node;
		}
		Iterator& operator++()
		{
			cur = cur->next;
			return *this;
		}
		Iterator& operator--()
		{
			cur = cur->prev;
			return *this;
		}
		T get_now() {
			return cur->data;
		}
		bool operator ==(T right)
		{
			return cur->data == right;
		}
		bool operator !=(Iterator it) {
			return cur != it.cur;
		}
	};
	Iterator begin()
	{
		Iterator i;
		i.set(base->next);
		return i;
	}
	Iterator end()
	{
		Iterator i;
		i.set(base);
		return i;
	}
	void push(T new_el)
	{
		node<T>* tmp = new node<T>;
		tmp->data = new_el;
		tmp->next = base;
		tmp->prev = base->prev;
		tmp->prev->next = tmp;
		base->prev = tmp;
		current = tmp;
	}
	bool empty() const
	{
		if(base->next == base)
			return true;
		return false;
	}
	void del_el()
	{
		if(empty())
			return;
		node<T> *tmp = current;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = base->next;
		delete tmp;
	}
	void clean()
	{
		if(empty())
			return;
		node<T> *p = base->next, *m;
		while (p != base)
		{
			m = p;
			p = p->next;
			delete m;
		}
		base->next = base;
		base->prev = base;
		current = base;

	}
	void one_next()
	{
		current = current->next;
		if(current == base)
			current = base->next;
	}

	void one_prev()
	{
		current = current->prev;
		if(current == base)
			current = base->prev;
	}
	T get_current()
	{
		if(current == base)
			throw CLASSERROR(-2, string("error"));
		return current->data;
	}
	void print() const
	{
		if(empty()) 
		{
			cout << "нет элементов" << endl;
			return;
		}
		node<T> *tmp = base->next;
		while(tmp != base)
		{
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}

	BiCircleList<T>& operator=(const BiCircleList<T>& right)
	{
		clean();
		node<T>* tmp = right.base->next;
		while (tmp != right.base)
		{
			push(tmp->data); 
			tmp = tmp->next;
		}
		current = base->next;
		return *this;
	}
};


int main()
{
	try
	{
		int i;
		cout << "новый тест: \n"; 
		BiCircleList<int> a;
		for(i = 0; i < 10; ++i)
			a.push(i);
		a.print();
		for(i = 0; i <= 15; ++i) a.del_el();
		a.print();

		cout << "\nновый тест:\n";
		//тестируем оператор присваивания
		for(i = 1; i <= 4; ++i) a.push(i);
		cout << "a: ";
		a.print();
		BiCircleList<int> b;
		b = a;
		cout << "b: ";
		b.print();

		cout << "\nновый тест\n";
		b.clean();
		b.push(3);
		b.push(13);
		b.del_el();
		b.push(14);
		b.push(10);
		b.print();

		cout << "\nновый тест:\n";
		a.clean();
		a.print();

		cout << "\nновый тест:\n";
		//тест итератора
		BiCircleList<int> d;
		for(i = 1; i <= 4; ++i)
			d.push(i);
		BiCircleList<int>::Iterator it = d.begin();
		bool flag = 0;
		for(i = 1; it != d.end(); ++it) {
			cout << it.get_now() <<  " ";
			if(!(it == i))
			{
				cout << "итератор не работает\n"; 
				flag = 1;
				break;
			}
			++i;
		}
		if(!flag) cout << "все хорошо!\n";
	}
	catch(CLASSERROR &err)
	{
		cout << err.get_reason() << endl;
	}
	return 0;
}
