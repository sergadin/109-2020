#include <iostream>
#include <stdexcept>
#include <cmath>
#include "list_arr.h"

using namespace std;

template <typename T>
list_arr<T>::list_arr()
{
    mem_size_ = 10;
    head_ = tail_ = new node(len_arr_);
}


template <typename T>
list_arr<T>::list_arr(size_t len)
{
    if(len == 0 )
    {
        throw list_arr_exception(ERR_ARR_LEN, "Size of block should be more than 0");
    }
    mem_size_ = len;
    len_arr_ = len;
    head_ = tail_ = new node(len);
}
template <typename T>
list_arr<T>::list_arr(const list_arr<T> & that)
{
    node *tmp = that.head_;
    while(tmp != nullptr ) 
    {
        node* newNode = new node(tmp->data_, that.len_arr_, nullptr, tail_);
        if(head_ == nullptr)
            head_ = newNode;
        if(tail_ != nullptr)
            tail_->next_ = newNode;
        tail_ = newNode;
        tmp = tmp->next_;
    }
    len_arr_ = that.len_arr_;
    mem_size_ = that.mem_size_;
}
template <typename T>
list_arr<T>::list_arr(list_arr<T> && that)
{
    head_ = that.head_;
    tail_ = that.tail_;
    len_arr_ = that.len_arr_;
    mem_size_ = that.mem_size_;
}

template <typename T>
list_arr <T>::~list_arr() 
{
    printf("dest_list\n");
    while(head_ != nullptr) 
    {
        node *tmp = head_;
        head_ = head_->next_;
        delete tmp;
    }
}
template <typename T>
list_arr<T> & list_arr<T>::operator = (list_arr<T> && that)
{
    this->clear();
    
    mem_size_ = that.mem_size_;
    head_ = that.head_;
    tail_ = that.tail_;
    len_arr_ = that.len_arr_;
    
    return *this;
}

template <typename T>
list_arr <T> & list_arr<T>::operator = (const list_arr<T> & that) 
{
    this->clear();
    
    node *tmp = that.head_;
    while(tmp != nullptr ) 
    {
        node* newNode = new node(tmp->data_, that.len_arr_, nullptr, tail_);
        if(head_ == nullptr)
            head_ = newNode;
        if(tail_ != nullptr)
            tail_->next_ = newNode;
        tail_ = newNode;
        tmp = tmp->next_;
    }
    
    mem_size_ = that.mem_size_;
    len_arr_ = that.len_arr_;
    return *this;
}

template <typename T>
void list_arr<T>::clear() 
{
    while(head_ != nullptr) 
    {
        node *tmp = head_;
        head_ = head_->next_;
        delete tmp;
    }
    head_ = tail_ = nullptr;
    mem_size_ = 0;
}



template <typename T>
T * list_arr<T>::front() 
{
    if(head_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is empty");
    T *temp = new T[len_arr_];
    for(size_t i = 0; i < len_arr_; i++)
    {
        temp[i] = head_->data_[i];
    }
    return temp;
}

template <typename T>
T * list_arr<T>:: back() 
{
    if(tail_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is emptyn'");
    T *temp = new T[len_arr_];
    for(size_t i = 0; i < len_arr_; i++)
    {
        temp[i] = tail_->data_[i];
    }
    return temp;
}

template <typename T>
void list_arr<T>::pop_front() 
{
    if(head_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is empty");
        
    node *tmp = head_;
    
    head_ = head_->next_;
    if(head_ != nullptr)
        head_->prev_ = nullptr;
    else
        tail_ = nullptr;    
    delete tmp;
    mem_size_ -= len_arr_;
}

template <typename T>
void list_arr<T>::pop_back() 
{
    if(head_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is empty");
    
    node *tmp = tail_;
    
    tail_ = tail_->prev_;
    if(tail_ != nullptr)
        tail_->next_ = nullptr;
    else
        head_ = nullptr;
    delete tmp;
    mem_size_ -= len_arr_;
}

template <typename T>
bool list_arr<T>::empty() const 
{
    return head_ == nullptr;
}

template <typename T>
size_t list_arr<T>::size() const 
{
    return mem_size_;
}

template <typename T>
T& list_arr<T>::operator[] (const size_t idx) 
{
    if(idx >= mem_size_)
    {
        throw list_arr_exception(INDEX_ERR, "Wrong index");
    }
    
    size_t cont = 0;
    size_t idx_list = (size_t)idx/len_arr_;
    size_t idx_arr = idx % len_arr_;
    
    node *curr = head_;
    while(curr) 
    {
        if(cont == idx_list)
            return curr->data_[idx_arr];
        curr = curr->next_;
        ++cont;
    }
    return curr->data_[idx_arr];
}


template <typename T>
void list_arr<T>::expand(size_t  expd_size)
{
    expd_size = (size_t)ceil( (double)expd_size/len_arr_);
    
    for(size_t i = 0; i < expd_size; i++  )
    {
        if( this->empty() )
        {
            head_ = tail_ = new node(len_arr_);
            continue;
        }
        
        tail_ = new node(len_arr_, nullptr, tail_);
        (tail_->prev_)->next_ = tail_;
    }
    mem_size_ += expd_size*len_arr_;
}

template <typename T>
void list_arr<T>::shrink(size_t shrk_size)
{
    if(head_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is empty");
    
    shrk_size = (size_t)ceil( (double)shrk_size/len_arr_);
    
    for(size_t i = 0; i < shrk_size; i++)
    {
        this->pop_back();
    }
    
}
