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
		indSel = IdName(wordsVector[0]);
		indBuy = IdName(wordsVector[1]);
		
		/*DaMatr[indSel][indBuy].ListOD::push_front(indSel, indBuy, stoi(wordsVector[2]), stoi(wordsVector[3]), stoi(wordsVector[4]), stoi(wordsVector[5]));
		cout << "No" << endl;
		//DaMatr->Matrix::NewDeal(*DaMatr, 1, 0, 3, 5, 6, 10);
		cout << "Lol" << endl; 
		//DaMatr->Matrix::NewDeal(*DaMatr, indSel, indBuy, stoi(wordsVector[2]), stoi(wordsVector[3]), stoi(wordsVector[4]), stoi(wordsVector[5]));
		cout << "No&" << endl;*/
		//std::reverse(begin(wordsVector), end(wordsVector));
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

	//RecordDeals(char nameM[]);
	
}			

int DataBase::IdName(string Name){
	int count=-1;
	for (i = VectofNames.begin(); i != VectofNames.end(); i++ ){
		if (Name == *i) return count+1;
		count++;
	}
	if (count == -1) 
		VectofNames.push_back(Name);
	return count+1;	
}
	
