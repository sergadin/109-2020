#include <iostream>
#include "cl.h"
#include <string>
#include <cstdlib>

using namespace std;

cl::cl(int n, int k) {
    if((n < 0) || (k < 0) || (k > n - 1))
        throw UserException(-1, "incorrect size");
    x_ = (int *)malloc(sizeof(int) *n);
    n_ = n;
    k_ = k;
    for(int i = 0; i < n_; i++)
        x_[i] = 0;
}


cl::cl (const cl &a) {
	n_ = a.n_;
	n_ = a.n_;
	x_ = (int *)malloc(sizeof(int) *n_);
	for(int i = 0; i < n_; i++)
		x_[i] = a.x_[i];
}




cl cl::operator =(const cl &right) {
	if(this == &right)
		return *this;
	n_ = right.n_;
	k_ = right.k_;
	free(x_);
	x_ = (int *)malloc(sizeof(int) *n_);
	for(int i = 0; i < n_; i++)
		x_[i] = right.x_[i];
	return *this;
}


cl::~cl() {
    free(x_);
}

void cl::send() {
    x_[k_]++;
}

cl& cl::receve(const cl &b) {
    if(n_ != b.n_)
        throw UserException(-2, "sizes are not equal");
    if(k_ == b.k_) 
        throw UserException(-3, "you can't send message to yourself");
    for(int i = 0; i < n_; i++) {
        if(x_[i] < b.x_[i])
            x_[i] < b.x_[i];
    }
    return *this;
}

bool operator<=(const cl& a, const cl& b) {
    if(a.n_ != b.n_)
        throw UserException(-4, "incomparable labels");
    bool result = true;
    for(int i = 0; i < a.n_; i++) {
        if(a.x_[i] > b.x_[i]) {
            result = false;
            break;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream &os,const cl& a) {
    os << "process " << a.k_ << ": (";
    for(int i = 0; i < a.n_ - 1; i++)
        os << a.x_[i] << ", ";
    os << a.x_[a.n_] << ")";
    return os;
}
