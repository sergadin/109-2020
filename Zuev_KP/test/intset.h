#include <iostream>
#include <string>

class IntSetError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		QueueError(int code, const std::string& reason)
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
		int size_; // Размер массива е1ements_ 
		int n_; // Число элементов в очереди

		void shift_left(); // сдвиг массива elenents_ на один элемент налево.
	public: 
		// Создание пустой очереди с максимальным размером size
		Queue (unsigned int size); 
		Queue (const Queue& obj); // Создать копию объекта obj
		~Queue();

		// Добавить item в конец очереди 
		void put(int item);

		int get_first();

		bool is_empty() const 
		{ 
			return n_ == 0;
		} 
		bool is_full() const 
		{
			return n_ == (size_ - 1);
		}

		void clear();

		Queue & operator=(const Queue & right);

		friend Queue& operator+= (Queue &left, const Queue& right);
		friend std::ostream& operator<<(std::ostream &os, const Queue& q);
};

















