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
	class Iterator {
	private:
		list_node<T> *cur_ = nullptr;
	public:
		Iterator() = default;
		Iterator &operator++(int em) {
			cur_ = cur_->next;
			return *this;
		}
		T get_now() {
			return cur_->data;
		}
		void set(list_node<T> *new_node) {
			cur_ = new_node;
		}
		Iterator &operator =(Iterator it){
			cur_ = it.cur_;
			return *(this);
		}
		bool operator ==(T x) {
			if(cur_->data == x)
				return true;
			else
				return false;
		}
		bool operator !=(Iterator it) {
			return cur_ != it.cur_;
		}
	};
	Iterator begin() {
		Iterator i;
		i.set(base_->next);
		return i;
	}
	Iterator end() {
		Iterator i;
		i.set(base_);
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
	void advance(T new_el, int pos) {
		if(pos <= 0) return;
		list_node<T> *p = new list_node<T>, *help = base_, *tmp;
		p->data = new_el;
		for(int i = 1; i < pos; ++i)
			help = help->next;
		tmp = help->next;
		help->next = p;
		p->next = tmp;
		current_ = p;
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
		cout << "Test1\n";
		List<int> test;
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		for(int i = 0; i <= 8; ++i)//тут взяли больше удалений, чем есть в списке
			test.del_cur();
		test.print();
		
		cout << "Test2\n";//лист test теперь пустой
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		List<int> test2;
		test2 = test;
		test2.print();
		
		cout << "Test3\n";
		test.del_all();
		test.print();
		
		cout << "Test4\n";
		List<int> not_last;
		not_last.print();
		cout << "Test5\n";
		List<int> last;
		last.advance(6, 1);
		last.advance(5, 1);
		last.advance(4, 1);
		last.advance(3, 1);
		last.advance(2, 1);
		last.advance(1, 1);
		List<int>::Iterator it = last.begin();
		for(int i = 1; it != last.end(); it++, i++) {
			cout << it.get_now() << ") ";
			if(it == i)
				cout << "+\n";
			else
				cout << "-\n";
		}
	}
	catch(ListException &err) {
		cout << err.get_error() << endl;
	}
	return 0;
}