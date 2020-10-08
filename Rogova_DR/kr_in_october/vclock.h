
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
class Vclock
{ 
	private: 
		int *elements_; 
		int N_; // Размер массива е1ements_ 
		int k_;
	public: 
		Vclock (int N, int k); 
		~Vclock();
		void local_ev(); 
		void global_ev(const Vclock& M); 
		friend bool operator <= (const Vclock& lev, const Vclock& prav);
		friend std::ostream& operator<<(std::ostream &os, const Vclock& q);
		Vclock & operator=(const Vclock & prav);


};


















