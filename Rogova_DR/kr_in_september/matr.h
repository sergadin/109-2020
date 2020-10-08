
#include <iostream>
#include <string>

class MatrError 
{
	private:
		int code_;
		std::string reason_;
		
	public:
		MatrError(int code, const std::string&reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{
			return reason_;
		}
};
class Matr
{ 
	private: 
		int *elements_; 
		int size_; // Размер массива е1ements_ 
		int left_;
		int right_;
		int find_el(int el) const
                {
                        for(int k = 0; k <= size_; k++)
                        {
                                if(elements_[k] == el)
                                        return 1;
                        }
                        return 0;
                } 

	public: 
		Matr (int left, int right); 
		Matr(const Matr& obj);
		~Matr();
		void put(int item); 
		void del_elem(int el); 
		bool is_empty() const 
		{ 
			return size_ == 0;
		} 
		int find_size();
		int minn();
		int maxx();
		int left_gr()
		{
			return left_;
		};
		int right_gr()
		{
			return right_;
		};
		Matr & operator= (const Matr & right);	
		friend Matr operator*(const Matr &lev, const Matr& prav);
		friend void operator*=(Matr &lev, const Matr& prav);
		friend std::ostream& operator<<(std::ostream &os, const Matr& q);
		friend bool operator== (const Matr& lev, const Matr& prav);

};


















