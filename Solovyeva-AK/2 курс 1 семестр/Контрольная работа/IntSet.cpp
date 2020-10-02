#include "IntSet.h"

IntSet::IntSet(int min, int max) {
    if (min > max) {
        throw UserException(3, "min > max");
    }
    array_ = (int*)calloc(10, sizeof(*array_));
    if (!array_) {
        throw UserException(2, "Memory Allocation Error");
    }
    size_ = 10;
    min_ = min;
    max_ = max;
    n_ = 0;
    array_[0] = 0;
}

IntSet::~IntSet(){
    free(array_);
}

int IntSet::CheckSize() const {
    return n_;
}

int IntSet::CheckMin() const {
    return array_[0];
}

int IntSet::CheckMax() const {
    if (n_ != 0) {
        return array_[n_-1];
    } else {
        return array_[n_];
    }
}

int IntSet::left() const {
    return min_;
}

int IntSet::right() const {
    return max_;
}

void IntSet::resize_(int newSize) {
    size_ = newSize;
    array_ = (int *)realloc(array_, size_*sizeof(*array_));
    if (!array_) {
        throw UserException(2, "Memory Allocation Error");
    }
    for (int i = n_; i < size_; i++) {
        array_[i] = 0;
    }
}

void IntSet::add_elem(int New_elem) {
    if (New_elem < min_) return;
    if (New_elem > max_) return;
    if (n_ == 0) {
        n_++;
        array_[0] = New_elem;
    } else {
        if (n_+1 >= size_) {
            this->resize_(size_*2);
        }
        int i = 0;
        while ((i < n_) && New_elem > array_[i]){
            i++;
        }
        if(New_elem == array_[i]) return;
        for(int j = n_; j > i; j--){
            array_[j] = array_[j-1];
        }
        array_[i] = New_elem;
        n_++;
    }
}

void IntSet::delete_elem(int d_elem) {
    if (n_ == 0) {
        return;
    } else {
        int i;
        for (i = 0; i < n_; i++) {
            if (array_[i] == d_elem) break;
        }
        if (i == n_) return;
        for (;i < n_ - 1; i++) {
            array_[i] = array_[i+1];
        }
        array_[n_-1] = 0;
        n_--;
    }
}

void IntSet::print() const {
    if (n_ == 0) cout << "no elements";
    for(int i = 0; i < n_; i++) {
        printf("%d ", array_[i]);
    }
    cout << endl;
}

void IntSet::operator =(const IntSet &other) {
    this->min_ = other.min_;
    this->max_ = other.max_;
    this->resize_(other.size_);
    for (int i = 0; i < other.n_; i++) {
        this->add_elem(other.array_[i]);
    }
}

bool IntSet::operator ==(const IntSet &other) {
    if (this->min_ != other.min_) return false;
    if (this->max_ != other.max_) return false;
    if (this->n_ != other.n_) return false;
    for(int i = 0; i < n_; i++) {
        if (this->array_[i] != other.array_[i]) return false;
    }
    return true;
}

IntSet IntSet::operator *(const IntSet &other){
    IntSet res(0,0);
    int min_max;
    int max_min;
    if (this->max_ > other.max_) {
        min_max = other.max_;
    } else {
        min_max = this->max_;
    }
    if (this->min_ > other.min_) {
        max_min = this->min_;
    } else {
        max_min = other.min_;
    }
    if (max_min < min_max) {
        res.min_ = max_min;
        res.max_ = min_max;
        for (int i = 0; i < this->n_; i++) {
            int tmp = this->array_[i];
            res.add_elem(tmp);
        }
        for (int i = 0; i < other.n_; i++) {
            int tmp = other.array_[i];
            res.add_elem(tmp);
        }
    }
   return res;
}

void IntSet::operator *=(const IntSet &other){
    int min_max;
    int max_min;
    if (this->max_ > other.max_) {
        min_max = other.max_;
    } else {
        min_max = this->max_;
    }
    if (this->min_ > other.min_) {
        max_min = this->min_;
    } else {
        max_min = other.min_;
    }
    if (max_min < min_max) {
        this->min_ = max_min;
        this->max_ = min_max;
        for (int i = 0; i < this->n_; i++) {
            if (this->array_[i] < this->min_){
                this->delete_elem(this->array_[i]);
            }
            if (this->array_[i] > this->max_){
                this->delete_elem(this->array_[i]);
            }
        }
        for (int i = 0; i < other.n_; i++) {
            int tmp = other.array_[i];
            this->add_elem(tmp);
        }
    }
}

UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
