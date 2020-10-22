#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

typedef struct list{
    list *next;
    int data;
} list;

template<typename T>
class stack {
    private:
        stack *next;
        T data;
    public:
    
        class Iterator{
            private:
                T *current;
            public:
                Iterator();
                Iterator (Iterator &other);
                T& operator +(int n);
                T& operator -(int n);
                T& operator ++();
                T& operator --();
                bool operator !=(const Iterator &it);
                bool operator ==(const Iterator &it);
                T& operator *();
        }
        Iterator begin();
        Iterator end();
        
        stack();
        stack(int elem);
        stack(const stack &other);
        ~stack();
        void operator =(const stack &other);
        bool operator ==(const stack &other) const;
        stack operator +(const stack &other);
        void print() const;
        int checkVoid() const;
        void push(int n);
        double pop();
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
