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
		int find(int item) const
                {
                        for(int k = 0; k < n_; k++)
                        {
                                if(elements_[k] == item)
                                        return 1;
                        }
                        return 0;
                } 
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
	
		friend IntSet operator*(const IntSet &lev, const IntSet& prav);
		friend bool operator== (const IntSet& lev, const IntSet& prav);
		friend void operator*= (IntSet &lev, const IntSet& prav);		
};

