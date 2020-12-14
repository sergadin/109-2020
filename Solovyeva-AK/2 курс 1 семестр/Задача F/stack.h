#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
struct list_item{
    list_item<T> *next;
    T data;
};


template<typename T>
class stack {
    private:
        list_item<T> *topElem_;
    public:
        class Iterator {
            private:
                friend class stack<T>;
                list_item<T> *current_;
            public:
                Iterator () {
                    current_ = nullptr;
                }
                Iterator& operator=(const Iterator &it)
				{
					current_ = it.current_;
					return *this;
				}

                void operator ++() {
                    if (current_ != nullptr) current_ = current_->next;
                    return;
                }
                bool operator !=(const Iterator &it) {
                    if(current_ != it.current_) return true;
                    return false;
                }
                bool operator ==(const Iterator &it) {
                    if(current_ == it.current_) return true;
                    return false;
                }
                friend T& operator *(const Iterator &it) {
                    return it.current_->data;
                }
        };
        Iterator begin() {
            Iterator tmp;
            tmp.current_ = topElem_;
            return tmp;
        }
        Iterator end(){
            Iterator tmp;
            tmp.current_ = topElem_;
            if(tmp.current_ == nullptr) return tmp;
            while(tmp.current_->next != nullptr){
                tmp.current_ = tmp.current_->next;
            }
            return tmp;
        } 
        
        stack();
        stack(T elem);
        stack(const stack &other);
        ~stack();
        void operator =(const stack &other);
        bool operator ==(const stack &other) const;
        stack operator +(const stack &other);
        void print() const;
        bool checkVoid() const;
        void push(T n);
        T pop();
        void clean();
};

class UserException {
	private:
		int code_;
		std::string message_;
	public:
		UserException(int code, std::string message);
		std::string message() const;
		int code() const;
};


template<typename T>
stack<T>::stack() {
    topElem_ = nullptr;
}


template<class T>
stack<T>::stack(T elem) {
    topElem_ = nullptr;
    push(elem);
}
template<class T>
stack<T>::stack(const stack<T> &other) {
    list_item<T>* p;
    list_item<T>* p2;
    list_item<T>* p3;

    topElem_ = nullptr;
    p3 = nullptr;

    p = other.topElem_;
    while (p != nullptr) {
        p2 = (list_item<T>*)malloc(sizeof(list_item<T>));
        if (!p2) {
            throw UserException(2, "Memory Allocation Error");
        }
        p2->data = p->data;
        p2->next = nullptr;
        if (topElem_ == nullptr) {
            topElem_ = p2;
            p3 = p2;
        } else {
            p3->next = p2;
            p3 = p3->next;
        }
        p = p->next;
    }
}

template<class T>
stack<T>::~stack(){
    clean();
}

template<class T>
void stack<T>::operator =(const stack<T> &other) {
    if (!checkVoid()) clean();

    list_item<T>* p;
    list_item<T>* p2;
    list_item<T>* p3;

    topElem_ = nullptr;
    p3 = nullptr;

    p = other.topElem_;
    while (p != nullptr)
    {
        push(p->data);
        p = p->next;
    }
}

template<class T>
bool stack<T>::operator ==(const stack &other) const {
    list_item<T> p;
    list_item<T> p2;
    p = topElem_;
    p2 = other.topElem_;
    while(p != nullptr && p2 != nullptr) {
        if (p->data != p2->data) return false;
        p = p->next;
        p2 = p->next;
    }
    if (p == nullptr && p2 == nullptr) return true;
    else return false;
}

template<class T>
stack<T> stack<T>::operator +(const stack &other) {
    stack<T> tmp;
    list_item<T> *p = this->topElem_;
    while (p != nullptr)
    {
        tmp.push(p->data);
        p = p->next;
    }
    p = other.topElem_;
    while (p != nullptr)
    {
        tmp.push(p->data);
        p = p->next;
    }
    return tmp;
}

template<class T>
void stack<T>::print() const {
    if (topElem_ == nullptr) {
        cout << "stack is empty." << endl;
    } else {
        list_item<T>* p;
        p = topElem_;
        while (p != nullptr) {
            cout << p->data << "\t";
            p = p->next;
        }
        cout << endl;
    }
}

template<class T>
bool stack<T>::checkVoid() const {
    if (topElem_ == nullptr) return true;
    else return false;
}

template<class T>
void stack<T>::push(T n) {
    list_item<T>* p;
    p = (list_item<T>*)malloc(sizeof(list_item<T>));
    if(!p) {
        throw UserException(3, "Memory Allocation Error");
    }
    p->data = n;
    p->next = topElem_;
    topElem_ = p;
}

template<class T>
T stack<T>::pop() {
    if(checkVoid()) return 0;
    list_item<T>* p2;
    T data;
    data = topElem_->data;
    p2 = topElem_;
    topElem_ = topElem_->next;
    free(p2);
    return data;
}

template<class T>
void stack<T>::clean(){
    list_item<T>* p;
    list_item<T>* p2;

    p = topElem_;
    
    while (p != nullptr)
    {
        p2 = p;
        p = p->next;
        free(p2); 
    }
    topElem_ = nullptr;
}




UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
