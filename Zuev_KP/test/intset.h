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

		/*
		bool is_empty() const //Пустота
		{ 
			return n_ == 0;
		} 
		bool number() const 
		{
			return n_ == (size_ - 1);
		}*/

		IntSet & operator=(const IntSet & right);

		friend IntSet& operator*= (IntSet &left, const IntSet& right);
		friend std::ostream& operator<<(std::ostream &os, const IntSet& q);
		//friend IntSet operator* (const IntSet &left, const IntSet& right);
};

/*
Исключение элемента из множества.
Проверка пустоты множества.
Получение минимального / максимального значения, содержащегося в множестве.
Получение границ множества (left, right).
Пересечение двух множеств, пересечение множества с другим множеством (операторы * и *=).
Проверка равенства множеств (оператор сравнения ==).
*/
















