#include "Dek.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iostream>

template<typename T>
Dek<T>::Dek(){
	size = 0;
	Head = nullptr;
	Tail = nullptr;
}

template<typename T>
Dek<T>::~Dek(){
	while (size) pop_front();
}

template<typename T>
void Dek<T>::pop_front(){
	
	if (size <= 0){
		return;
	}
	Node *temp = Head;
	Head = Head -> Next;
	delete temp;
	size --;
}

template<typename T>
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
	Head -> Pvev = temp; //указтель из головы на предыдущий, это новый элетемент
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