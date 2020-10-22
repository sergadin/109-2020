#include <string>
#include "Time.h"
#include <iostream>
#include <stdio.h>
#include <cstring>



PortrPart::PortrPart (const std::string& NameOfProgr, int SizeOfMasKat){
	int i = 0;
	if (SizeOfMasKat < 0 || SizeOfMasKat == 0){
		throw Error(-1, std::string("Размер не может быть отрицательным"));
	}
		
	MasofOperInKat_ = new int [SizeOfMasKat];
	MasofSumInEvKat_ = new double [SizeOfMasKat];
	NameOfProgr_ = NameOfProgr;
	
	SizeOfMasKat_ = SizeOfMasKat;
	
	for (i = 0; i < SizeOfMasKat; i++){
		MasofOperInKat_[i] = 0;
		MasofSumInEvKat_[i] = 0;
	}
}

PortrPart::~PortrPart(){
	delete[] MasofSumInEvKat_;
	delete[] MasofOperInKat_;
}

void PortrPart::SpendMoney(int InWhatKat, double HowMuch){
	if (InWhatKat >= SizeOfMasKat_){
		printf("Такой категории нет");
		throw Error(-3, std::string("Такой категории нет"));
	}
	MasofOperInKat_[InWhatKat] +=1;
	MasofSumInEvKat_[InWhatKat] +=HowMuch;
	return;
}

void Check(const PortrPart &Par1, const PortrPart &Par2){
	if (Par1.NameOfProgr_ == Par2.NameOfProgr_  && Par1.SizeOfMasKat_ == Par2.SizeOfMasKat_){
		printf("Тут два одинаковых человека\n");
		for (int  i = 0; i < Par1.SizeOfMasKat_; i++){
			Par1.MasofOperInKat_[i] += Par2.MasofOperInKat_[i];
			Par2.MasofOperInKat_[i] = Par1.MasofOperInKat_[i];
			Par1.MasofSumInEvKat_[i] += Par2.MasofSumInEvKat_[i];
			Par2.MasofSumInEvKat_[i] = Par1.MasofSumInEvKat_[i];
		}

	}
	else {
		printf("Человеки разные\n");
	}
		
}

	
bool operator <= (const PortrPart &Par1, const PortrPart &Par2){
	double Sum1 = 0, Sum2 = 0; 
	//if (strcmp((const char*)(Par1.NameOfProgr_), (const char*)(Par2.NameOfProgr_)) == 0){
	/*std::cout << "---------------------------------" << std::endl; 
	std::cout << Par1.NameOfProgr_<< std::endl; 
	std::cout << Par2.NameOfProgr_<< std::endl; 
	std::cout << (Par1.NameOfProgr_ == Par2.NameOfProgr_) << std::endl;
	std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;*/
	if (Par1.NameOfProgr_ == Par2.NameOfProgr_  && Par1.SizeOfMasKat_ == Par2.SizeOfMasKat_){
		for (int i=0; i < Par1.SizeOfMasKat_; i++){
		Sum1 += Par1.MasofSumInEvKat_[i];
		Sum2 += Par2.MasofSumInEvKat_[i];
		}
		if (Sum1 < Sum2){
			printf("Второй лояльнее\n");
			return true;
		}
		
		if (Sum1 <= Sum2 && Sum1 >=Sum2){
			printf("Их лояльность одинаковая\n");
			return true;
		}
		
		if (Sum1 > Sum2){
			printf("Первый лояльнее\n");
			return false;
		}
	}
	else{	
		printf("Не тех сравниваете\n");
		throw Error (-2, std::string("Не тех сравниваете"));
		return false;
	}
}
	
std::ostream & operator<<(std::ostream &os, const PortrPart &Par)
{
	/*if (Par.MasofOperInKat_ == nullptr || Par.MasofSumInEvKat_ == nullptr){
		throw(-3, std::string("Такого человека уже нет, а может и не было"));
	}
*/
	os << "Количество категорий " << Par.SizeOfMasKat_ << "  Количество операций в каждой категории и количество денег \n";
	for(int i = 0; i < Par.SizeOfMasKat_; i ++)
	{
		os << Par.MasofOperInKat_[i] << "  " << Par.MasofSumInEvKat_[i]  << "\n";
	}
	printf("\n\n\n");
	return os;

}
	