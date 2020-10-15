#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

typedef struct list{
    list *next;
    int data;
} list;


class stack {
    private:
        list *head;
        
    public:
        stack();
        stack(int elem);
        stack(const stack &other);
        void operator =(const stack &other);
        bool operator ==(const IntSet &other);
        stack operator +(const stack &other);
        void SortStack();//точно ли нужна функция сортировки для стека?
        void print() const;
        int checkVoid() const;
        void push(int n);
        double pop();
        void clean();
        ~stack();
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
