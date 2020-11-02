#include <iostream>

template <class T>

class list
{
private:
	T val_;
	list *next_;
	list *prev_;
public:
	explicit list();
	list(const T first_item)
	{
		val_ = first_item;
		prev_ = 0;
		next_ = 0;
	}
	friend void deletelist(list <T> *L)
	{
		if (L->next_ == 0)
			std::cout << "L->next_ = 0\n";
		else
			std::cout << "L->next_ != 0";
		while (L->prev_ != 0)
		{
			L = L->prev_;
			delete (L->next_)->prev_;
			delete L->next_;
		}
	}
	~list()
	{
		deletelist(this);
	}
	list <T> put_item(const T item)
	{
		std::cout << "NO\n\n\n";
		list *p = new list <T>(val_);
		std::cout << "YES\n\n\n";
		p->prev_ = prev_;
		p->next_ = this;
		if (prev_ != 0)
			prev_->next_ = p;
		prev_ = p;
		val_ = item;
		std::cout << "YES YES\n\n\n";
		return *this;
	}
};






























/*#include <string>
#include <iostream>

class ClockError
{
	private:
		int code_;
		std::string reason_;
	public:
		ClockError(int code, std::string reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string get_reason() const
		{
			return reason_;
		}
};

class Clock
{
	private:
		int N_; // количество процессов
		int *mark_; // набор из N_ чисел
		int num_; // номер процесса 0..(N-1)
	public:
		explicit Clock();
		Clock(int N, int num)
		{
			if ((N <= 0) || (num >= N))
				throw ClockError(-3, std::string("Недопустимые значения параметров\n"));
			N_ = N;
			num_ = num;
			mark_ = new int[N];
			for (int i = 0; i < N; i++)
				mark_[i] = 0;
		}
		Clock(const Clock &C)
		{
			N_ = C.N_;
			num_ = C.num_;
			mark_ = new int[N_];
			for (int i = 0; i < N_; i++)
				mark_[i] = C.mark_[i];
		}
		~Clock()
		{
			delete[] mark_;
			N_ = num_ = 0;
		}

		friend Clock nextClock(const Clock &C);
		friend Clock nextClock(const Clock &prevClock, const Clock &sendingClock);

		Clock operator=(const Clock &C);		

		friend bool operator<(const Clock &left, const Clock &right);
};*/