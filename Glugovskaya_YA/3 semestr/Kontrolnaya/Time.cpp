#include <string>
#include "Time.h"
#include <iostream>


Time::Time(int size, int Met){
	if (size < 0){
		throw TimeError(-1, std::string("Размер не может быть отрицательным"));
	}
	
	if (Met_ >= size - 1){
		throw TimeError(-2, std::string("Значение больше размера массива"));
	}
	
	MasofTime_ = new int[size];
	size_=size;
	Met_=Met;
	for (int i=0; i<size; i++)
		MasofTime_[i] = 0;
}

Time::~Time(){
	delete[] MasofTime_;
}

void Time::InEvent(){
	MasofTime_[Met_] +=1;
}

void Time::GetMessage(const Time & Getter){
	
	if (Getter.size_ != size_){
		throw TimeError (-3, std::string("Размеры не соответствуют"));
		return;
	}
	
	if (Met_ == Getter.Met_){
		for (int i = 0; i<size_; i++){
			if (MasofTime_[i] != Getter.MasofTime_[i]){
				throw TimeError(-4, std::string("Нельзя получить сообщение"));
			}
		}
		return;
	}
	
	
	for(int i = 0; i < size_; i ++){
		if(i != Met_){
			if(Getter.MasofTime_[i] > MasofTime_[i]){
				MasofTime_[i] = Getter.MasofTime_[i];		
			}	
		}
		else
		{
			MasofTime_[i] += 1;
		}
	}
	std::cout << "Получение сообщения" << this <<std::endl;
}

bool operator <= (const Time& Sender, const Time& Getter){
	if(&Sender == &Getter){
         return true;
    }
	
	if(Sender.size_ != Getter.size_){
		throw TimeError(-5, std::string("Разные размеры получателя и отправителя"));
		return false;
	}
	
	for(int i = 0; i < Sender.size_; i ++){
		if(Sender.MasofTime_[i] > Getter.MasofTime_[i]){
			return false;
		}
	}
	return true;
}
	
Time& Time::operator=(const Time & Sender){
        if(this == &Sender){
            return *this;
        }
        delete[] MasofTime_;
        MasofTime_ = new int[Sender.size_];
		size_ = Sender.size_;
        Met_ = Sender.Met_;
        for(int i = 0; i < size_; i++)
	{
                MasofTime_[i] = Sender.MasofTime_[i];
	}
        return *this;
}

std::ostream & operator<<(std::ostream &os, const Time&q)
{
	os << "Введите количество процессов " << q.size_ << "  Введите количество событий: \n" << q.Met_;
	for(int i = 0; i < q.size_; i ++)
	{
		os << "\t" << q.MasofTime_[i] << "\n";
	}
	return os;

}