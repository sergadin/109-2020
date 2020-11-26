#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
struct list{
    list<T> *next;
    T data;
};


template<typename T>
class stack {
    private:
        list<T> *topElem;
    public:
        list<T>* begin();
        list<T>* end();
        
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

template<typename T>
class Iterator{
    private:
        list<T> *current;
    public:
        Iterator (list<T>* other);
        Iterator (Iterator &other);
        void operator ++();
        bool operator !=(const Iterator &it);
        bool operator ==(const Iterator &it);
        T& operator *();
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
Iterator<T>::Iterator(list<T> *other){
    current = other;
}

template<typename T>
list<T>* stack<T>::begin() {
    return topElem;
}

template<typename T>
list<T>* stack<T>::end() {
    list<T>* p = topElem;
    if(p == nullptr) return topElem;
    while(p->next != nullptr){
        p = p->next;
    }
}

template<typename T>
Iterator<T>::Iterator (Iterator &other){
    current = other.current;
}

template<typename T>
void Iterator<T>::operator ++(){
    if (current != nullptr) current=current->next;
    return;
}

template<typename T>
bool Iterator<T>::operator !=(const Iterator &it){
    if(current != it.current) return true;
    return false;
}

template<typename T>
bool Iterator<T>::operator ==(const Iterator &it){
    if(current == it.current) return true;
    return false;
}

template<typename T>
T& Iterator<T>::operator *(){
    return current->data;
}


template<typename T>
stack<T>::stack() {
    topElem = nullptr;
}


template<class T>
stack<T>::stack(T elem) {
    topElem = nullptr;
    push(elem);
}
template<class T>
stack<T>::stack(const stack<T> &other) {
    list<T>* p;
    list<T>* p2;
    list<T>* p3;

    topElem = nullptr;
    p3 = nullptr;

    p = other.topElem;
    while (p != nullptr) {
        p2 = (list<T>*)malloc(sizeof(list<T>));
        if (!p2) {
            throw UserException(2, "Memory Allocation Error");
        }
        p2->data = p->data;
        p2->next = nullptr;
        if (topElem == nullptr) {
            topElem = p2;
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

    list<T>* p;
    list<T>* p2;
    list<T>* p3;

    topElem = nullptr;
    p3 = nullptr;

    p = other.topElem;
    while (p != nullptr)
    {
        push(p->data);
        p = p->next;
    }
}

template<class T>
bool stack<T>::operator ==(const stack &other) const {
    list<T> p;
    list<T> p2;
    p = topElem;
    p2 = other.topElem;
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
    list<T> *p = this->topElem;
    while (p != nullptr)
    {
        tmp.push(p->data);
        p = p->next;
    }
    p = other.topElem;
    while (p != nullptr)
    {
        tmp.push(p->data);
        p = p->next;
    }
    return tmp;
}

template<class T>
void stack<T>::print() const {
    if (topElem == nullptr) {
        cout << "stack is empty." << endl;
    } else {
        list<T>* p;
        p = topElem;
        while (p != nullptr) {
            cout << p->data << "\t";
            p = p->next;
        }
        cout << endl;
    }
}

template<class T>
bool stack<T>::checkVoid() const {
    if (topElem == nullptr) return true;
    else return false;
}

template<class T>
void stack<T>::push(T n) {
    list<T>* p;
    p = (list<T>*)malloc(sizeof(list<T>));
    if(!p) {
        throw UserException(3, "Memory Allocation Error");
    }
    p->data = n;
    p->next = topElem;
    topElem = p;
}

template<class T>
T stack<T>::pop() {
    if(checkVoid()) return 0;
    list<T>* p2;
    T data;
    data = topElem->data;
    p2 = topElem;
    topElem = topElem->next;
    free(p2);
    return data;
}

template<class T>
void stack<T>::clean(){
    list<T>* p;
    list<T>* p2;

    p = topElem;
    
    while (p != nullptr)
    {
        p2 = p;
        p = p->next;
        free(p2); 
    }
    topElem = nullptr;
}




UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
