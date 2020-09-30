#include "text.h"


queue::queue() {
    n = 0;
    size = 10;
    array = (double*)malloc(size*sizeof(*array));
    if (!array) {
        throw UserException(1, "Memory Allocation Error");
    }
}

queue::queue(int new_size) {
    n = 0;
    size = new_size;
    array = (double *)malloc(size*sizeof(*array));
    if (!array) {
        throw UserException(1, "Memory Allocation Error");
    }
}

void queue::resize(int new_size) {
    size = new_size;
    array = (double *)realloc(array, size*sizeof(*array));
    if (!array) {
        throw UserException(2, "Memory Allocation Error");
    }
}

int queue::checkVoid() const {
    if (n == 0) {
        return 1;
    } else {
        return 0;
    }
}

int queue::checkfull() const {
    if (n == size) {
        return 1;
    } else {
        return 0;
    }
}

void queue::clean() {
    free(array);
    n = 0;
    size = 0;
}

void queue::push(double elem) {
    if (n == size) return;
    array[n] = elem;
    n++;
}

double queue::pop() {
    double res = array[0];
    for (int i = 1; i < n; i++) {
        array[i-1] = array[i];
    }
    array[n-1] = 0;
    n--;
    return res;
}

void queue::print() const {
    if (n == 0) cout << "no elements";
    for(int i = 0; i < n; i++) {
        printf("%.2lf ", array[i]);
    }
    cout << endl;
}
int queue::CheckSize() const{
    return n;
}
queue queue::operator +(const queue &other) {
    queue res(this->n + other.n);
    for(int i = 0; i < this->n; i++) {
        res.push(this->array[i]);
    }
    for(int i = 0; i < other.n; i++) {
        res.push(other.array[i]);
    }
    return res;
}

queue::~queue() {
    free(array);
    n = 0;
    size = 0;
}

UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}