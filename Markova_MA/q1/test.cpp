#include <iostream>
#include <cstdio>
#include <math.h>
#include <string>
using namespace std; 

class ListException {
private:
	int code_;
	string reason_;
public:
	ListException(int code, const string &reason) {
		code_ = code;
		reason_ = reason;
	}
	const string &get_error() const {
		return reason_;
	}
};

template <typename T>
struct list_node {
	T data;
	list_node *next;
};

template <typename T>
class List {
private:
	list_node<T> *base_;
	list_node<T> *current_;
public:
	class Iterator {
	private:
		list_node<T> *cur_;
		Iterator() {
			cur_= new list_node<T>;
			current_ = base_;
			current_.go_next();
			cur_->data = current_->data;
			cur_->next = current_->next;
		}
		~Iterator() {
			delete cur_;
		}	
	public:
		Iterator &operator++(Iterator &i) {
			i.cur_ = i.cur_->next;
			return i;
		}
		T get_now() {
			return cur_->data;
		}
		bool operator ==(Iterator &now) {
			if(this == now)
				return true;
			else
				return false;
		}
	};
	List() {
		base_ = new list_node<T>;
		base_->next = base_;
		current_ = base_;
	}
	~List() {
		current_ = base_;		
		del_all();
		delete base_;
	}
	Iterator begin() {
		Iterator i();
		return i;
	}
	void push_back(T new_el) {
		list_node<T> *p = new list_node<T>, *help = base_->next;
		p->data = new_el;
		p->next = base_;
		while(help->next != base_)
			help = help->next;
		current_ = help;
		current_->next = p;
		current_ = p;
	}
	bool is_empty() const {
		if(base_->next == base_)
			return true;
		else
			return false;
	}
	void del_cur() {
		if(is_empty())
			return;
		list_node<T> *tmp = current_, *help = base_;
		while(help->next != current_)
			help = help->next;
		help->next = current_->next;
		current_ = base_->next;
		delete tmp;
	}
	void del_all() {
		if(is_empty())
			return;
		list_node<T> *help = base_->next;
		list_node<T> *m;
		current_ = base_;
		while (help != base_) {
			m = help;
			help = help->next;
			delete m;
		}
		base_->next = base_;
	}
	void go_next() {
		current_ = current_->next;
		if(current_== base_)
			current_ = base_->next;
	}
	T get_current() {
		if(current_ == base_)
			throw ListException(-1, string("error"));
		return current_->data;
	}
	void print() const {
		if(is_empty()) {
			cout << "List is empty!\n";
			return;
		}
		list_node<T> *p;
		p = base_->next;
		while (p->next != base_) {
			cout << p->data << "->";
			p = p->next;
		}
		cout << p->data;
		cout << endl;
	}
	List<T> &operator=(const List<T> &now) {
		list_node<T> *p;
		del_all();
		current_ = base_;
		p = now.base_->next;
		while (p != now.base_) {
			push_back(p->data); 
			p = p->next;
		}
		current_ = base_->next;
		return *this;
	}
};


int main() {
	try {
		/////Test1: (Добавляем 5 элементов = i от 1, затем удаляем 8 элементов)
		List<int> test;
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		for(int i = 0; i <= 8; ++i)//тут взяли больше удалений, чем есть в списке!
			test.del_cur();
		test.print();
		cout << "___________________________\n";
		//// Test2: (тестируем оператор присваивания) лист test теперь пустой
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		List<int> test2;
		test2 = test;
		test2.print();
		cout << "___________________________\n";
		//////Test3: (тестируем удаление всех элементов)
		test.del_all();
		test.print();
		cout << "___________________________\n";
		////Test4: (Попробуем-ка вывести пустой список)
		List<int> last;
		last.print();
	}
	catch(ListException &err) {
		cout << err.get_error() << endl;
	}
	return 0;
}