#include <iostream>
#include <string>

class VectorError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		VectorError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};


class Vector 
{ 
	private: 
		int *elements_;
		int n_; 
		int k_;
		int size_;
	public: 
		Vector (int n, int k); 
		Vector (const Vector& obj);
		~Vector();
};

