#include <iostream>
#include <stdexcept>
#include "list_arr.h"

using namespace std;

template <typename T>
list_arr<T>::list_arr()
{
    mem_size_ = 10;
    real_size_ = 0;
    head_ = tail_ = new node(len_arr_);
}


template <typename T>
list_arr<T>::list_arr(size_t len)
{
    mem_size_ = len;
    len_arr_ = len;
    real_size_ = 0;
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
    real_size_ =  that.real_size_;
    len_arr_ = that.len_arr_;
    mem_size_ = that.mem_size_;
}
template <typename T>
list_arr<T>::list_arr(list_arr<T> && that)
{
    real_size_ = that.real_size_;
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
    real_size_ = that.real_size_;
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
    real_size_ =  that.real_size_;
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
    real_size_ = 0;
}



template <typename T>
T * list_arr<T>::front() 
{
    if(head_ == nullptr)
        throw list_arr_exception(EMPTY, "Array is empty");
    T *temp = new T[len_arr_];
    for(int i = 0; i < len_arr_; i++)
    {
        temp[i] = head_->data_[i];
    }
    return temp;
}

template <typename T>
T * list_arr<T>:: back() 
{
    if(tail_ == nullptr)
        throw list_arr_exception(EMPTY, "Array doesn't have a tail");
    T *temp = new T[len_arr_];
    for(int i = 0; i < len_arr_; i++)
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
    
    real_size_ = real_size_ - len_arr_;
    
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
    real_size_ = real_size_ - len_arr_;
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
    if(idx >= mem_size_ || idx < 0)
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
    expd_size = (size_t)expd_size/len_arr_;
    
    for(int i = 0; i < expd_size; i++  )
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


int main(void) 
{
    list_arr<int> A;
    
    try
    {
        int *c;
        list_arr<int> b;
        for(int i  = 0; i < 10; i++)
        {
            A[i]  = i;
        }
        b = A;
        b[2] = 15651;
        cout << "oparator= cheak: " << b[2] <<endl;
        c = b.front();
        cout << "func front cheak: " << c[6] <<endl;
        delete[] c;
        b = A;
        c = b.back();
        cout << "func back cheak: " << c[9] <<endl;
        b.pop_front();
        cout << "func pop_front cheak: " << b.empty() << endl;
        cout << "func size() cheak: b.size(): " << b.size() << endl;
        b = A;
        b.pop_back();
        cout << "func pop_back cheak: " << b.empty() << endl;
        cout << "func size() cheak: b.size(): " << b.size() << endl;
        b.expand(40);
        b[29] = 1265;
        cout << "func expand cheak: b.size(): " << b.size() << " b[29]:" << b[29] << endl;
        
        delete[] c;
        
        
    }
    catch (list_arr_exception &err)
    {
		std::cout << "EXC  "<< err.get_reason() << std::endl;
    }
    return 0;
}
