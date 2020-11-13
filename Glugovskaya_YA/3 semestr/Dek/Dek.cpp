#include "Dek.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iostream>

template<typename T>
Deque<T>::Deque(){
	size_ = 0;
	Head_ = NULL;
	Tail_ = NULL;
}

template<typename T>
Deque<T>::~Deque(){
	while (size_) pop_front();
}

template<typename T>
void Deque<T>::pop_front(){
	
	if (size_ <= 0){
		throw Error(-1, std::string("Дальше удалять нечего"));
	}
	Node *temp = Head_;
	Head_ = Head_ -> Next_;
	Head_ -> Prev_  = Tail_;
	Tail_ -> Next_ = Head_;
	delete temp;
	size_ --;
}

template<typename T>
void Deque<T>::pop_back(){
	
	if (size_ <= 0){
		throw Error(-1, std::string("Дальше удалять нечего"));
	}
	Node *temp = Tail_;
	Tail_ = Tail_ -> Prev_;
	Tail_ -> Next_  = Head_;
	Head_ -> Prev_ = Tail_;
	delete temp;
	size_ --;
}

template <typename T>
void Deque<T>:: front(){
	cout << "front: " << Head_ -> data_ << endl;
}

template <typename T>
void Deque<T>:: back(){
	cout << "back: " << Tail_ -> data_ << endl;
}

template <typename T>
void Deque<T>:: push_front(T data)
{
	Head_ = new Node(data, Head_, Tail_);
	
	if (size_ == 0) {
		Tail_= Head_;
		Head_ -> Next_ = Head_ -> Prev_ = Head_;
	}
	else {
		Tail_ -> Next_ = Head_;
		(Head_ -> Next_) -> Prev_ = Head_;
	}
    size_++;
}

template <typename T>
void Deque<T>:: push_back(T data){
	
	Tail_ = new Node(data, Head_, Tail_);
	
	if (size_ == 0) {
		Head_= Tail_;
		Tail_ -> Next_ = Tail_ -> Prev_ = Tail_;
	}
	else {
		Head_ -> Next_ = Tail_;
		(Tail_ -> Next_) -> Prev_ = Tail_;
	}
    size_++;
}




/*template <typename T>
ostream& operator<<(std::ostream& os, const Deque<T> & Deck);
template<typename T>
Dek<T>::Dek(T data){
	size = 1;
	Head = new Dek<T>::Node;
	Head -> Prev = nullptr;
	Head -> Next = nullptr;
	Head -> data = data;
}

*/
template<typename T>
void Deque<T>::print(){
	int count = 0;
	Deque<T>::Node*current = this->Head_;
	cout << "----------New print----------" << endl;
	while (count < (this->size_)){
		cout << "Current " << current << "   Data "<< current -> data_ << "   Next " << current -> Next_ << "   Prev " << current ->Prev_  << endl;
		current = current -> Next_;
		cout << current << endl;
		count ++;
	}
}

template class Deque<int>;
template class Deque<double>;
template class Deque<char>;
template class Deque<float>;

