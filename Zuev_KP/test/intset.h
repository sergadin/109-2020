#include <iostream>
#include <string>

class IntSetError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		IntSetError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};


class IntSet 
{ 
	private: 
		int *elements_;
		int a_; 
		int b_;
		int size_;
		int n_;

	public: 
		IntSet (int a, int b); 
		IntSet (const IntSet& obj);
		~IntSet();

		void put(int item); //Добавление		
		
		void exc(int item); //Исключение

		bool is_empty() const //Пустота
		{ 
			return n_ == 0;
		}
		
		int max(); //Макс

		int min(); //Мин

		int lima(); //Left
		
		int limb(); //Right

		IntSet & operator=(const IntSet & right);

		friend std::ostream& operator<<(std::ostream &os, const IntSet& q);

		friend IntSet& operator*= (IntSet &left, const IntSet& right);		
		friend IntSet operator* (const IntSet &left, const IntSet& right);
		friend bool operator== (const IntSet &left, const IntSet &right);
};

/*
Пересечение двух множеств, пересечение множества с другим множеством (операторы * и *=).
Проверка равенства множеств (оператор сравнения ==).
*/
















