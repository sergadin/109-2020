#include <iostream>
#include <stdio.h>
#include <cstring>
#include <list>
#include "S.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(){
	DataBase UserBase;
	setlocale(LC_ALL, "Russian");
 
  //  cout << "Укажите имя файла, где лежит список продавцов и покупателей: " << endl;
    char nameS[40];
   // cin.getline(nameS, 40);
	 // ofstream out1(nameS, ios::app);
	cout << "Укажите имя файла, где хранятся сделки: " << endl;
    char nameM[40];
    cin.getline(nameM, 40);
   // ofstream out2(nameM, ios::app);
	//UserBase.GetNames(nameS, nameM);
	//UserBase.showNames();	
	UserBase.RecordDeals(nameM);
	return 0;
}