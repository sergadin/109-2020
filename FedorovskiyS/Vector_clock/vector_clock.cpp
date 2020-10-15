#include <iostream>
#include <string>
#include "vector_clock.h"

vector_clock::vector_clock(unsigned int dim, unsigned int index){
    if((index > dim) || (index == 0) || (dim == 0)){
        throw error_vector_clock(-1, std::string("Ошибка определения!"));
    }
    index_ = index;
    dim_ = dim;
    time_ = new unsigned int[dim_];
    for(int i = 0; i < dim_; ++i){
        time_[i] = 0;
    }
}

vector_clock::~vector_clock() {
    delete[] time_;
}

void vector_clock::sign(){
    time_[index_ -1]++;
}

void vector_clock::message(const vector_clock &x){
    if(dim_ != x.dim_){
        throw error_vector_clock(-2, std::string("Разные размерности!"));
    }
    for(int i = 0; i < x.dim_; ++i){
        if(time_[i] < x.time_[i])
            time_[i] = x.time_[i];
    }
    sign();
}

bool operator <(const vector_clock &x, const vector_clock &y){
    if(y.dim_ != x.dim_){
        throw error_vector_clock(-2, std::string("Разные размерности!"));
    }
    bool flag = 0;
    for(int i = 0; i < x.dim_; ++i){
        if(x.time_[i] <= y.time_[i]){
        if(x.time_[i] < y.time_[i])
            flag = 1;
        }
        else return 0;
    }
    if (flag == 1)
        return 1;
    return 0;
}

void vector_clock::print_vector_clock(){
    for(int i = 0; i < dim_; ++i){
        std::cout << time_[i];
    }
    std::cout << std::endl;
}

vector_clock & vector_clock::operator=(const vector_clock &x){
    if(this == &x){
        return *this;
    }
    delete[] time_;
    time_ = new unsigned int[x.dim_];
    dim_ = x.dim_;
    index_ = x.index_;
    for(int i = 0; i < dim_; ++i){
        time_[i] = x.time_[i];
    }
    return *this;
}
