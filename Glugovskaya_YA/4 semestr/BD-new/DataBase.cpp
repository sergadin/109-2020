#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include "S.h"
#include <typeinfo>
using namespace std;

DataBase::DataBase(){ 
	
}

void DataBase::RecordDeals(char nameM[]){
	ifstream ifs;
	string NamePerson;			
	ifs.open(nameM);
	string tmpStr;
	vector<string>::iterator j;
	std::vector<std::string> wordsVector;
	int indSel, indBuy;
	
	if ( !ifs.is_open() ) {
		cerr << "Can't open file" << endl;
	}
	
	
	while(ifs){		
		getline(ifs, tmpStr);
		istringstream iss(tmpStr, istringstream::in);
	    string word;			
				
		while( iss >> word ){   //почему-то в вектор всё дважды записывается
			wordsVector.push_back(word);			
		}
		cout << "word[0] " << wordsVector[0] << endl;
		indSel = NameId(wordsVector[0]);
		cout << "indSel" << indSel << endl;
		indBuy = NameId(wordsVector[1]);
		
		cout<<"Yes"<<endl;
		/*ListOD Ex = (*DaMatr)[indSel][indBuy];	
		cout << "ok" << endl;
		cout << Ex << endl;
		cout << "ok" << endl;*/
		cout << typeid((*DaMatr)[indSel][indBuy]).name() << endl;
		cout << "ok" << endl;
		ListOD &Ex = (*DaMatr)[indSel][indBuy];
		cout << "ok1" << endl;
		cout << Ex << endl;
		cout << "Ook" << endl;
		(*DaMatr)[indSel][indBuy].push_front(indSel, indBuy, stoi(wordsVector[2]), stoi(wordsVector[3]), stoi(wordsVector[4]), stoi(wordsVector[5]));
		cout << "No" << endl;
		cout << "No3" << endl;
		
	}
	for (j = wordsVector.begin(); j != wordsVector.end(); j++ )
		cout << *j << endl;
	
}

void DataBase::GetNames(char nameS[], char nameM[]){
	ifstream ifs;
	string NamePerson;			
	ifs.open(nameS);
	if ( !ifs.is_open() ) {
		cerr << "Can't open file" << endl;
	}
	int N=0;
	while ( !ifs.eof() ){
		getline(ifs, NamePerson);
		VectofNames.push_back(NamePerson);
		N++;
	}
	
	ifs.close();
	
	for (i = VectofNames.begin(); i != VectofNames.end(); i++ )
		cout << *i << endl;
					
												
	setN(N);

	RecordDeals(nameM);
	
}			

int DataBase::NameId(string Name){
	int count=0;
	for (i = VectofNames.begin(); i != VectofNames.end(); i++ ){
		cout << "Name in vect " <<  *i << endl;
		if (Name == *i) {
			cout << "Нашли " << Name << " номером " << count << endl; 
			return count;
		}
		count++;
	}
	cout << "Добавили " << Name <<" Элементом: " << count << endl; 
	VectofNames.push_back(Name);
	
	return count;	
}

void DataBase::AddDeal(string NewDeal){
	std::vector<std::string> wordsVector;
	istringstream iss(NewDeal, istringstream::in);
	string word;	
	int indSel, indBuy;	
				
	while( iss >> word ){   //почему-то в вектор всё дважды записывается
		wordsVector.push_back(word);			
	}
	indSel = NameId(wordsVector[0]);
	cout << "indSel" << indSel << endl;
	indBuy = NameId(wordsVector[1]);
	(*DaMatr)[indSel][indBuy].push_front(indSel, indBuy, stoi(wordsVector[2]), stoi(wordsVector[3]), stoi(wordsVector[4]), stoi(wordsVector[5]));
		
}
	
