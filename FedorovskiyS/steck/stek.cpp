#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class stekException {
	int code_;
	string reason_;
public:
	stekException(int code, const string &reason) {
		code_ = code;
		reason_ = reason;
	}
	const string &get_string() const {
		return reason_;
	}
};

template <typename T>
struct node {
	T data;
	node *next;
};

template <typename T>
class stek {
private:
	node<T> *root;
	node<T> *current;
public:
	stek() {
		root = new node<T>;
		root->next = nullptr;
		current = nullptr;
	}
	~stek() {
		clear();
		delete root;
	}
	class Iterator {
	private:
		node<T> *cur = nullptr;
	public:
		Iterator() = default;
		Iterator &operator++(int fict) {
			if(cur == nullptr)
				throw stekException(-1, string("There is no element."));
			cur = cur->next;
			return *this;
		}
		T get_now() {
			if(cur == nullptr)
				throw stekException(-4, string("There is no element."));
			return cur->data;
		}
		void set(node<T> *new_node) {
			cur = new_node;
		}
		Iterator &operator =(Iterator it){
			cur = it.cur;
			return *(this);
		}
		bool operator ==(T x) {
			if(cur->data == x)
				return true;
			return false;
		}
		bool operator !=(Iterator it) {
			return cur != it.cur;
		}
	};
	Iterator begin() {
		Iterator i;
		i.set(root->next);
		return i;
	}
	Iterator end() {
		Iterator i;
		i.set(nullptr);
		return i;
	}
	
	void push(T x) {
		node<T> *p = new node<T>, *btw = root->next;
		p->data = x;
		root->next = p;
		p->next = btw;
	}
	void push_pos(T x, int pos) {
		if(pos <= 0) return;
		node<T> *p = new node<T>, *btw = root, *tmp;
		p->data = x;
		for(int i = 1; i < pos && btw; ++i)
			btw = btw->next;
		if(btw == nullptr) {
			delete p;
			throw stekException(-2, string("There is no element."));
		}
		tmp = btw->next;
		btw->next = p;
		p->next = tmp;
		current = p;
	}
	bool is_empty() const {
		if(root->next == nullptr)
			return true;
		return false;
	}
	void pop() {
		if(is_empty())
			return;
		node<T> *tmp = root->next;
		root->next = root->next->next;
		delete tmp;
	}
	void clear() {
		if(is_empty()) return;
		node<T> *btw = root->next, *m;
		current = nullptr;
		while(btw != nullptr) {
			m = btw;
			btw = btw->next;
			delete m;
		}
		root->next = nullptr;
	}
	void go_next() { 
		if(current == nullptr)
			throw stekException(-10, string("There is no element."));
		current = current->next; 
	}
	T top() {
		if(current == nullptr)
			throw stekException(-3, string("There is no element."));
		return current->data;
	}
	void print() const {
		if(is_empty()) {
			cout << "stek is empty\n";
			return;
		}
		node<T> *p;
		p = root->next;
		while(p != nullptr) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	stek<T> &operator=(const stek<T> &x) {
		node<T> *p;
		clear();
		p = x.root->next;
		int i = 1;
		while(p != nullptr) {
			push_pos(p->data, i);
			++i;
			p = p->next;
		}
		current = root->next;
		return *this;
	}
};


int main() {
	try {
		cout << "Test1: \n"; 
		//Добавляем 4 элементов, затем удаляем 5 элементов
		stek<int> a;
		a.push(1);
		a.push(2);
		a.push(3);
		a.push(4);
		a.print();
		for(int i = 0; i <= 5; ++i) a.pop();
		a.print();
		cout << "\n";

		cout << "Test2:\n";
		//тестируем оператор присваивания
		for(int i = 1; i <= 4; ++i) a.push(i);
		cout << "a: ";
		a.print();
		stek<int> b;
		b = a;
		cout << "b: ";
		b.print();
		cout << "\n";
		cout << "Test3: (тестируем удаление всех элементов)\n";
		a.clear();
		a.print();
		cout << "\nTest4:\n";
		//тест итератора
		stek<int> d;
		d.push_pos(6, 1);
		d.push_pos(5, 1);
		d.push_pos(4, 1);
		d.push_pos(3, 1);
		d.push_pos(2, 1);
		d.push_pos(1, 1);
		stek<int>::Iterator it = d.begin();
		for(int i = 1; it != d.end(); it++, i++) {
			cout << it.get_now() << ") ";
			if(it == i) cout << "ok\n";
			else cout << "ko\n";
		}
	}
	catch(stekException &error) {
		cout << error.get_string() << endl;
	}
	return 0;
}