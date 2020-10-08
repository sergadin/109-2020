#include "class.h"

int Max2(int a, int b) {
    if (a > b) return a;
    else return b; 

}
///////////////////////////
VectorClock::VectorClock(int dimension, int index) {
    if ((dimension < 1) || (index < 1))
        throw UserException(1, "wrong data:((((");
    if (index > dimension)
        throw UserException(4, "wrong index or dim :((((");
    dimN_ = dimension;
    indexK_ = index;
    data_ = new unsigned int[dimN_ ];
    for (int i = 0; i < dimN_; i++)
        data_[i] = 0;
};

void VectorClock::print() {
     for(int i = 0; i < dimN_; i++)
         std::cout << data_[i];
     std::cout << endl;
};

void VectorClock::LocalEvent() {
    data_[indexK_-1]++;
};

void VectorClock::EventMessage(const VectorClock &process) {
    if ((dimN_ != process.dimN_))
        throw UserException(2, "different dimensions:((((");
    if ((indexK_ == process.indexK_))
        throw UserException(3, "smth completely wrong:((((");
    int backup;
    for (int i = 0; i < dimN_; i++) {
        backup = Max2(data_[i], process.data_[i]);
        data_[i] = backup;
    }
    this->LocalEvent();
};

VectorClock::~VectorClock() {
    delete[] data_;
};

bool operator<(const VectorClock& left, const VectorClock& right) {
    if (left.dimN_ != right.dimN_)
        throw UserException(2, "different dimensions:((((");
    int count = 0;
    for (int i = 0; i < left.dimN_; i++) {
        if (left.data_[i] > right.data_[i])
            return false;
        if (left.data_[i] < right.data_[i])
            count++;
    };

    if (count == 0)
        return false;

    return true;
};

/////////////////////////////
UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
    return message_;
}

int UserException::code() const {
    return code_;
}
