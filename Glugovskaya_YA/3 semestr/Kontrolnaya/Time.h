#include <iostream>
#include <string>

class Time 
{
	private:
		int size_;
		int *MasofTime_ ;
		int Met_;
	public:
		Time(int size, int Met);
		~Time();
		void InEvent();
		void GetMessage(const Time &obj);
		friend bool operator <= (const Time &Sender, const Time &Getter);
		friend std::ostream& operator<<(std::ostream &os, const Time& q);
		Time & operator = (const Time & Getter);
		
};


class TimeError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		TimeError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};

