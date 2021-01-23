#pragma once
#include <iostream>
#include <cstring>

class bonusError
{
private:
	int code_;
	std::string reason_;
public: 
	bonusError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};

class bonus 
{
	private: 
		int *actions_;
		double *money_;
		std::string name_;
		int n_; // сколько категорий
	public: 
		bonus(const std::string &name, int n); 
		~bonus();
		void act();
		void dollars(int category, double m);
        friend bool operator == (const bonus &N, const bonus &M);
		friend void samePerson(const bonus &fperson, const bonus &sperson);
        friend std::ostream& operator<<(std::ostream &os, const bonus &N);
};


