#include <iostream>
#include <cstdio>

using namespace std;

class UserException {
	private:
		int code_;
		std::string reason_;
	public:
		UserException(int code, std::string reason):code_(code), reason_(reason){}
		std::string reason() const{
            return reason_;
        }
		int code()const{
            return code_;
        }
};

template <typename T>
struct list_ {
	T data;
	list_ *next;
	list_ *prev;
};

template <typename T>
class list {
	private:
		list_<T> *head;
		list_<T> *curr; 
		list_<T> *tail;
	public:

        bool is_empty() {
			return (head->next == tail);
		}

		list() {
			head = new list_<T>;
			tail = new list_<T>;
			head->prev = head;
			tail->next = tail;
			head->next = tail;
			tail->prev = head;
			curr = head;
		}

		list(const list& a) {
			list_<T>* p;
			head = new list_<T>;
			tail = new list_<T>;
			head->next = tail;
			head->prev = head;
			tail->prev = head;
			tail->next = tail;
			curr = head;
			p = a.head;
			p = p->next;
			while (p != a.tail) {
				add_after(p->data);
				p = p->next;
			}
			curr = head->next;
		}

		~list() {
			curr = head;		
			del_all();
			delete head;
			delete tail;
		}

        void go_next() {
			curr = curr->next;
			if(curr== tail)
				curr = tail->prev;
		}

		void go_prev() {
			curr= curr->prev;
			if(curr == head)
				curr = head->next;
		}

		void add_after(T el) {
			list_<T>* p;
			p = new list_<T>;
			p->data = el;
			p->next = tail;
			p->prev = tail->prev;
			tail->prev = p;
			curr = p->prev;
			curr->next = p;
			curr = p;
		}

		void del_el() {
			if(is_empty())
				return;
			if(curr == head)
				curr = curr->next;
			if(curr == tail)
				curr = curr->prev;
			if(curr == head)
				return;
			list_<T> * prev_el;
			prev_el = curr;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr = head->next;
			delete prev_el;
		}

        void del_head() {
            if (!is_empty()) {
                list_<T> *a;
                a = head;
                head= head->next;
                delete a;
            }
        }
    
		void del_all() {
            if (!is_empty()) {
			    list_<T> *a;
			    curr = head->next;
			    while (curr != tail) {
				    a = curr;
				    curr = curr->next;
				    delete a;
			    }
			    head->next = tail;
			    head->prev = head;
			    tail->prev = head;
			    tail->next = tail;
            }
		}

		void print() const {
			list_<T> *p;
			p = head->next;
			while (p != tail) {
				std::cout << p->data << "\t";
				p = p->next;
			}
			p = nullptr;
			std::cout << std::endl;
		}

		list<T>& operator=(const list<T>& right) {
			list_<T>* p;
			del_all();
			curr = head;
			p = right.head;
			p = p->next;
			while (p != right.tail) {
				add_after(p->data); 
				p = p->next;
			}
			curr = head->next;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream &out, const list<T> &a) {
			list_<T> *p;
			p = a.head->next;
			while (p != a.tail) {
				out << p->data << "\t";
				p = p->next;
			}
			p = nullptr;
			return out;
		}
};

int main() {
	try {
		list<int> a;
		a.add_after(1);
		a.add_after(10);
        a.add_after(100);
		a.print();
		a.del_head();
        a.print();
        a.del_el();
        a.del_el();
		a.print();
		list<int> b;
		b.add_after(2);
		b.add_after(3);
        b.add_after(4);
        b.add_after(3);
        b.add_after(5);
        b.add_after(7);
		b.print();
		a.del_all();
        a.print();
	}
	catch(UserException &err) {
		cout << err.reason() << endl;
	}
	return 0;
}
