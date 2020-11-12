#include <string>
#include <cstdio>
#include <math.h>

template<typename T>
struct list{
    list<T> *next;
    T data;
}


template<typename T>
class stack {
    private:
        list<T> *topElem;
    public:
    
        class Iterator{
            private:
                T *current;
            public:
                Iterator();
                Iterator (Iterator &other);
                Iterator& operator +(int n);
                Iterator& operator -(int n);
                Iterator& operator ++();
                Iterator& operator --();
                bool operator !=(const Iterator &it);
                bool operator ==(const Iterator &it);
                T& operator *();
        }
        Iterator begin();
        Iterator end();
        
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
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};
