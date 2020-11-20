#include <stdio.h>
#include <cstring>
#include <iostream>

class PortrPart 
{
	private:
		std::string NameOfProgr_;
		int *MasofOperInKat_ ;
		double *MasofSumInEvKat_ ;
		int SizeOfMasKat_;
		
	public:
		PortrPart (const std::string& NameOfProgr, int SizeOfMasKat);
		~PortrPart();
		PortrPart& operator=(const PortrPart &Par);
		void SpendMoney(int InWhatKat, double HowMuch);
		friend bool Check(const PortrPart &Par1, const PortrPart &Par2);
		friend bool operator <= (const PortrPart &Par1, const PortrPart &Par2);
		friend std::ostream& operator<<(std::ostream &os, const PortrPart &Par);
		
};


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

