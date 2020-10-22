#include <iostream>
#include <string>

class StackError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		StackError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};


class Stack 
{ 
	private: 
		int *elements_;
		int n_; 
		int k_;
	public: 
		Stack (int n, int k); 
		~Stack();
		Stack & operator=(const Stack & right);
		friend std::ostream& operator<<(std::ostream &os, const Stack& q);
};

