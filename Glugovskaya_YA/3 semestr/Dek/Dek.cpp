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
		return;
	}
	Node *temp = Head_;
	Head_ = Head_ -> Next_;
	delete temp;
	size_ --;
}

template <typename T>
void Deque<T>:: push_front(T data)
{
    Head_ = new Node(data, Head_, NULL);
    size_++;
}

template <typename T>
ostream& operator<<(std::ostream& os, const Deque<T> & Deck){
	Deque<T>::Node<T>* current;
	current = Deck.Head_;
	for (int i = 0; i < Deck.size_; i++){
	cout << current -> Deck.data_ << endl;
	current = current -> Deck.Next_;
	}
		
} 

/*template<typename T>
Dek<T>::Dek(T data){
	size = 1;
	Head = new Dek<T>::Node;
	Head -> Prev = nullptr;
	Head -> Next = nullptr;
	Head -> data = data;
}


template<typename T>	
void Dek<T>::push_head(T data){
	Dek<T>::Node *temp = new Dek<T>::Node; //делаем новый узел
	//заполняем нужные поля
	temp -> data = data; 
	temp -> Next = (Head -> Prev) -> Next;
	temp -> Prev = (Head -> Prev);
	(Head -> Prev) -> Next = temp; //Делаем от головы шаг назад, смотрим на указатель, который указывает на голову и присваиваем ему значение новой ячейки
	Head -> Prev = temp; //указтель из головы на предыдущий, это новый элетемент
	Head = temp; //теперь у нас новая голова
	size ++;
}

template<typename T>
void Dek<T>::print(){
	int count = 0;
	Dek<T>::Node*current = Head; 
	while (count != size){
		cout << current -> data << endl;
		current = current -> Next;
		count ++;
	}
}
*/
template class Deque<int>;
template class Deque<double>;
template class Deque<char>;
template class Deque<float>;

