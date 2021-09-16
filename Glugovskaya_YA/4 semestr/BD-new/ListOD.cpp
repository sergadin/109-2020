#include <iostream>
#include <iostream>
#include <string>
#include "S.h"
#include <typeinfo>

ListOD::ListOD(){
	size_=0;
	Head_ = nullptr;
	Tail_ = nullptr;
}

ListOD::~ListOD(){
	while (size_) pop_front();
}


void ListOD::pop_front(){
	DealInfo *temp = Head_;
	Head_ = Head_ -> Next_;
	Head_ -> Prev_  = Tail_;
	Tail_ -> Next_ = Head_;
	delete temp;
	size_ --;
}

void ListOD::push_front(int IndSell, int IndBuy, double Price,
				                int Day, int Mounth, int Year){
	cout << "Make push" <<endl;								
	Head_ = new DealInfo(IndSell, IndBuy, Price, Day, Mounth, Year, Head_, Tail_);
	
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