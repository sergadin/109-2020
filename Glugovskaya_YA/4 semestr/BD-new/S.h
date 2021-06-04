#include<iostream>
#include<windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <list>
#include <fstream>
using namespace std;

class ListOD{
	public:
		class DealInfo{
			public:
				int IndSell_;
				int IndBuy_;
				double Price_;
				int Day_;
				int Mounth_;
				int Year_;
				DealInfo * Next_;
				DealInfo * Prev_;
				DealInfo(int IndSell =0, int IndBuy=0,  double Price =0,
				                int Day=0, int Mounth = 0, int Year =0,
				               	DealInfo * Next = nullptr, DealInfo *Prev = nullptr){
					
					IndSell_ = IndSell;
					IndBuy_ = IndBuy;							
					Price_ = Price;
					Day_ = Day;
					Mounth_ = Mounth;
					Year_ = Year;
					Next_ = Next;
					Prev_ = Prev;				
				}
		};
		DealInfo*Head_;
		DealInfo *Tail_;
		int size_;
		
	public:	
		 ListOD();
		 ~ListOD();
		 void pop_front();
		 void push_front(int IndSell =0, int IndBuy=0, double Price =0,
				                int Day=0, int Mounth = 0, int Year =0);
		
		friend std::ostream& operator <<(std::ostream& os,const ListOD& List){
			DealInfo *current = List.Head_;
			for (int i=0; i <List.size_; i++){
				cout << current -> IndSell_ << " " << current -> IndBuy_ << " " <<  current -> Price_ <<  " " <<current -> Day_ <<  " " << current -> Mounth_ << " " << current -> Year_ << endl;
				current = current -> Next_;
			}		
		}		
		 
		
};




class Matrix
{
	private:
    ListOD *matrix_;
    int x_, y_;
 
    class Iterator{
    public:     
        ListOD *pRow;
        ListOD & operator[]( int i ){ return pRow[i]; }
 
        Iterator( ListOD* pRow ) : pRow( pRow ){}
    };      
 
public:
    Matrix();
 
    Iterator operator[]( int i )
    { 
        return &matrix_[i * y_]; 
    }  
    Matrix( int x, int y ) : x_( x ), y_( y ), matrix_(new ListOD[x * y])
    {}
    ~Matrix()
    {
        delete [] matrix_;
    }
	
	NewDeal(Matrix* DataMatrix_, int IndSell =0, int IndBuy=0,  double Price =0,
												int Day=0, int Mounth = 0, int Year =0){
			cout << "2" << endl;										
			//DataMatrix_[IndSell][IndBuy].ListOD::push_front(IndSell, IndBuy, Price, Day, Mounth, Year);
			cout << "3" << endl;										
		}
	
	  
	//Mail Google Milk 100000 10 12 1999
	friend ListOD;
};

	



class DataBase{
	private:
		Matrix *DaMatr;
		vector<string> VectofNames;
		vector<string>::iterator i;	
		
		
	public:
		DataBase();
		~DataBase(){ }
		friend Matrix;
		
		void  GetNames(char nameS[], char nameM[]);
		void setN(int N){
			Matrix *NewMatr = new Matrix(N,N);
			DaMatr=NewMatr;
		}
			
		void showNames(){
			for ( i = VectofNames.begin(); i != VectofNames.end(); i++ )
					cout << *i << endl;
		}
	
		void RecordDeals(char nameM[]);
	    int IdName(string Name); 
		
	
	
	friend Matrix;	
	friend ListOD;
};
		
		