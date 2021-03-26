#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

template <typename T>
class Deque{
	private:
		class Node{
			public:
				T data_;
				Node *Next_;
				Node *Prev_;
				Node(T data, Node *Next = NULL, Node *Prev = NULL){ //конструктор узла  
					data_  = data;
					Next_ = Next;
					Prev_ = Prev;
					}
		};
		Node *Head_;
		Node *Tail_;
		int size_;
		void swap(Deque<T>::Node* First, Deque<T>::Node* Second); //меняем местами два узла
		void copy(Deque<T>::Node* SydaCopy, Deque<T>::Node* OtsydaCopy); //копируем данные из одного узла в другой
				
	public:
	
		class Iterator{
			private:
				const Deque<T>* OurIterDeque_;
				int step_;
				Node *CurrentIt_;
				Iterator(Deque<T> * Deque, int index){ // 0 - голова, 1-хвост 
					OurIterDeque_ = Deque;
					step_=1;
					if (index == 0)	CurrentIt_ = Deque -> Head_;
					if (index == 1) CurrentIt_ = Deque -> Tail_;
				}


				Iterator(const Deque<T> * Deque, int index){ // 0 - голова, 1-хвост 
					OurIterDeque_ = Deque;
					step_=1;
					if (index == 0)	CurrentIt_ = Deque -> Head_;
					if (index == 1) CurrentIt_ = Deque -> Tail_;
				}
					
				public:
				friend class Deque;

				void print(){
					cout << "----------Данные об итераторе----------" << endl;
					cout << "OurIterDeque _ " << OurIterDeque_ << endl;
					cout << "CrrentIt_ " << CurrentIt_ << endl;
					cout << "Step_" << step_ << endl;
				}
				void parametrs(int start, int step){
					step_ = step;		
					for (int i = 0; i < start; i++){
						CurrentIt_  = CurrentIt_ -> Next_;
					}
				}
				Iterator& operator=(const Iterator& right){
					CurrentIt_= right.CurrentIt_;
					step_=right.step_;
					return *this;
				} 	
				Iterator& operator+(int n){
					n = n%( OurIterDeque_ -> size_);
					//cout << n << endl;
					for (int i=0; i < n; i++){
						CurrentIt_ = CurrentIt_  -> Next_;
					}
					return *this;
				}	
				
				Iterator& operator-(int n){
					n = n%( OurIterDeque_ -> size_);
					for (int i=0; i < n; i++){
						CurrentIt_ = CurrentIt_  -> Prev_;
					}
					return *this;
				}
	
				Iterator& operator++(int i){
					CurrentIt_ = CurrentIt_  -> Next_;
					return *this;
				}
	
				Iterator& operator--(int i){
					CurrentIt_ = CurrentIt_  -> Prev_;
					return *this;
				}
		
		};
		Iterator begin(){
			Iterator it(this, 0);
			cout << "--------Вывод итератора begin-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
		Iterator end(){
			Iterator it(this, 1);
			cout << "--------Вывод итератора end-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
	
	
		Iterator begin() const{
			Iterator it(this, 0);
			cout << "--------Вывод итератора begin const-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
		Iterator end() const{
			Iterator it(this, 1);
			cout << "--------Вывод итератора end const-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
			
					 
		Deque(); //конструктор
		~Deque(); //деструктор
		Deque(const Deque &D){	
			this -> Head_=NULL;	
			this -> Tail_ =NULL;
			this -> size_ = 0;	
			Node *p=D.Head_;	
			for (int i=0; i<D.size_; i++){	
			  push_front(p->data_);
			  p=p->Next_;	
			}
			/*cout << "(Copy constr)" << endl;
			Node* A;
			Node* B;
			Node* C = nullptr;
			Head_ = nullptr;
			A = D.Head_;
			while (A != D.Tail_){
				B = new Node(A->data_, nullptr, nullptr);
				if (Head_== nullptr){
					Head_ = A;
					C = B;
				}
				else {
					C -> Next_=B;
					C = C -> Next_;
				}
				A = A-> Next_;
			}*/
		};
	
		void pop_front(); //удаляем первый элемент из head
		void pop_back(); //удаляем в хвосте
		void push_front(T data); //заталкиваем в голову
		void push_back(T data);
		void print(); 
		void front();// печатаем первый элемент
		void back(); //печатаем последний элемент
		void sort(); //сортируем данные в деке пузырьком
		//Deque<T>& operator=(const Deque<T>& right);
		template <typename U> friend std::ostream& operator <<(std::ostream& os,const Deque<U>& Deck);
		int Deque_size();
		Deque<T>& operator=(Deque<T>& riqht);

};
template <typename T>
Deque<T>& Deque<T>::operator =(Deque<T>& right){
	while (this -> size_) this -> pop_front();
	//cout << "-- " <<typeid(&right).name() <<"   -------" << endl; 
	Iterator it = right.end();
	
	for (int i=0; i < right.size_ ; i++){
		push_front(it.CurrentIt_ -> data_);
		it--; 
	}
	return *this;
}
 

class Error
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		Error(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};

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
		Head_ -> Prev_ = Tail_;
		(Tail_ -> Prev_) -> Next_ = Tail_;
	}
    size_++;
}

template <typename T>
void Deque<T>:: copy(Deque<T>::Node* SydaCopy, Deque<T>::Node* OtsydaCopy){
	SydaCopy -> data_ = OtsydaCopy -> data_;
	//SydaCopy -> Next_ = OtsydaCopy -> Next_;
	//SydaCopy -> Prev_ = OtsydaCopy -> Prev_;
}	


	
template <typename T>
void Deque<T>::sort(){
	Deque<T>::Node* PosMaxData = Head_;
	Deque<T>::Node* current = Head_;
	//cout << "--------Сортируем---------" << endl;
	for (int  i = 0; i < size_; i++){
		PosMaxData = Head_;
		current= Head_;
		for (int  j = 0; j < size_ - i; j++){
			if ((PosMaxData -> data_) < (current -> data_)){
				PosMaxData = current;
			}
			current = current -> Next_;
		}
		swap(current -> Prev_, PosMaxData);
		print();
	}
}
			
		
template <typename T>
void Deque<T>:: swap(Deque<T>::Node* First, Deque<T>::Node* Second){
	Deque<T>::Node* temp = new Node(0, NULL, NULL);
	//if (First == Head_) Head_= Second;
	//if (Second == Head_) Head_= First;
	copy(temp, First);
	copy(First, Second);
	copy(Second, temp);
	delete temp;
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
		count ++;
	}
}

template <typename T>  
std::ostream& operator <<(std::ostream& os,const Deque<T>& Deck){ 
	//typename Deque<T>::Iterator it = Deck.begin();
	typename Deque<T>::Node*current = Deck.Head_;
	cout << "___________________Печать дека___________________" << endl;
	cout << "Head "<< Deck.Head_ << "     Tail " << Deck.Tail_ << endl;	
	for (int i =0; i < Deck.size_; i++){
		cout << "Current " << current << "   Data "<< current -> data_ << "   Next " << current -> Next_ << "   Prev " << current ->Prev_  << endl;
		current = current -> Next_;	 
	}
	return os;
}