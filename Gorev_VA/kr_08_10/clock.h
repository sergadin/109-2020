#include <string>
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
		Clock(int N, int num)
		{
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

		Clock &operator=(const Clock &C)
		{
			N_ = C.N_;
			num_ = C.num_;
			mark_ = C.mark_;
			
			for (int i = 0; i < N_; i++)
				std::cout << C.mark_[i] << " ";
			cout << endl;

			return *this;
		}

		friend Clock &operator<(const Clock &left, const Clock &right);
};










/*class intsetError
{
	private:
		int code_;
		std::string reason_;
	public:
		intsetError(int code, std::string reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string get_reason() const
		{
			return reason_;
		}

};

class intset
{
	private:
		int *ar_;
		int size_;
		int maxval_;
		int minval_;
	public:
		intset(int maxval, int minval);
		~intset();
		intset(intset& IS);
		intset(const intset& IS);
		explicit intset(); 
		bool find_item(int item) const; // найти элемент в множестве
		void put(int item); // добавить item в конец множества
		void del(int item); // удалить элементы со значением item из множества
		bool is_empty() const // проверка пустоты множества
		{
			return size_ == 0;
		}
		bool size() const // вычисление количества элементов множества
		{
			return size_;
		}
		int find_max() const; // максимальный элемент в множестве
		int find_min() const; // минимальный элемент в множестве
		int left_bord() const // левая граница множества
		{
			return minval_;
		}
		int right_bord() const // правая граница множества
		{
			return maxval_;
		}

		friend intset operator* (const intset &left, const intset &right); // пересечение двух множеств
		friend intset& operator*= (intset &left, const intset &right); // пересечение множества с другим множеством
		friend bool operator== (const intset &left, const intset &right);

};
*/