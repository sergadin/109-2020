#pragma once
#include <math.h>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class Exc
{
private:
	int code_of_error;
	string error;
public:
	Exc(int code, const string& reason);
	const string& get_error() const;
};

template <typename T>
class ListItem
{
public:
	T data;
	ListItem* next;
};

template <typename T>
class List
{
private:

	ListItem<T>* first;
	ListItem<T>* last;
public:
	class Iterator
	{
	private:
		friend class List<T>;
		friend class ListItem<T>;
		

	public:
		ListItem<T>* cur;
		Iterator()
		{
			cur = nullptr;
		}

		Iterator& operator ++(int f)
		{
			this->cur = this->cur->next;
			return *this;
		}

		friend T& operator*(const Iterator& i)
		{
			return i.cur->data;
		}

		friend bool operator !=(const Iterator& left, const Iterator& right)
		{
			if (left.cur != right.cur) return true;
			else return false;
		}

		void go_next()
		{
			this->cur = this->cur->next;
		}

		T get_it(const Iterator& i)
		{
			return i.cur->data;
		}

		Iterator& operator= (const Iterator& right)
		{
			cur = right.cur;
			return *this;
		}
	};

	List()
	{
		first = new ListItem<T>;
		first->next = first;
		last = first;
	}

	void push_back(T new_el)
	{
		ListItem<T>* p = new ListItem<T>;
		p->data = new_el;
		p->next = first;
		last->next = p;
		last = p;
	}

	List(const List& A)
	{
		ListItem<T>* p;
		first = new ListItem<T>;
		first->next = first;
		last = first;
		p = A.first;
		p = p->next;
		while (p != A.first)
		{
			this->push_back(p->data);
			p = p->next;
		}
	}

	~List()
	{
		last = first;
		del_all();
		delete first;
	}

	Iterator begin()
	{
		Iterator i;
		i.cur = first;
		return i;
	}
	Iterator end()
	{
		Iterator i;
		i.cur = first;
		i.next_go();
		while (i.cur != first) i.cur = i.cur->next;
		return i;
	}

	bool is_empty()
	{
		if (first->next == first)
			return true;
		else
			return false;
	}

	void del_all()
	{
		if (this->is_empty()) return;
		ListItem<T>* m;
		last = first->next;
		while (last != first)
		{
			m = last;
			last = last->next;
			delete m;
		}
		first->next = first;
	}

	T get_current()
	{
		if (last == first)	throw Exc(-2, string("it is empty list"));
		return last->data;
	}
	void print() const
	{
		ListItem<T>* p;
		p = first->next;
		while (p != first)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	List<T>& operator=(const List<T>& right)
	{
		ListItem<T>* p;
		List<T> temp(right);
		this->del_all();
		last = first;
		p = temp.first;
		p = p->next;
		while (p != temp.first)
		{
			this->push_back(p->data);
			p = p->next;
		}
		return *this;
	}

	List<T>& operator+(const List<T>& right)
	{
		Iterator i;
		i.cur = right.first;
		i++;
		while (i.cur != right.first)
		{
			this->push_back(i.cur->data);
			i++;
		}
		return *this;
	}

	List<T>& sort()
	{
		for (int i = 0; i < this->lenght(); i++) for (int j = i; j < this->lenght(); j++) if (this->at(i) > this->at(j))
		{
			T temp = this->at(i);
			this->at(i) = this->at(j);
			this->at(j) = temp;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const List<T>& H)
	{
		ListItem<T>* p;
		p = H.first->next;
		while (p != H.first)
		{
			out << p->data << " ";
			p = p->next;
		}
		return out;
	}

	int lenght()
	{
		int count = 0;
		Iterator i;
		i.cur = first;
		i++;
		while (i.cur != first)
		{
			count++;
			i++;
		}
		return count;
	}

	T at(int n)
	{
		if (this->lenght() == 0)
		{
			throw Exc(0, string("This list is empty"));
			return this->first->data;
		}
		int number = n % this->lenght();
		Iterator i;
		i.cur = first;
		for (int j = -1; j < number; j++) i++;
		return i.cur->data;
	}
};

