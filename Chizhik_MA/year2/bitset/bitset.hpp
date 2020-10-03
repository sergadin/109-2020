#include <iostream>
#include <climits>

class BitIntSet {
	private:	
		static int INT_CARDINALITY;

		int inf_;
		int sup_;

		int list_start_; //First bit of array refers to this number
		
		int len_;

		int* list_;
		int size_;

		int* cache_;
		int last_actual_cached_;
		int cache_len_;

		BitIntSet();
	public:
		BitIntSet(int left, int right);
		BitIntSet(const BitIntSet& set);
		~BitIntSet();

		void clear();
		bool empty() const { return len_ == 0; }
		int len() const { return len_; }

		void add(int a);
		void remove(int a);
		bool belongs(int a) const;

		int min() const;
		int max() const;

		int left() const { return inf_; }
		int right() const { return sup_; }

		int get(int index) const;
		int operator[](int index);

		friend BitIntSet operator*(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator+(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator-(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator^(const BitIntSet& A, const BitIntSet& B);

		BitIntSet& operator=(const BitIntSet& B);

		BitIntSet& operator*=(const BitIntSet& B);
		BitIntSet& operator+=(const BitIntSet& B);
		BitIntSet& operator-=(const BitIntSet& B);
		BitIntSet& operator^=(const BitIntSet& B);

		friend bool operator<=(const BitIntSet& A, const BitIntSet& B);
		friend bool operator==(const BitIntSet& A, const BitIntSet& B);

		friend std::ostream& operator<<(std::ostream& os, const BitIntSet& set);
};

class BitIntSetException {
	private:
		const int error_code_;
		const std::string reason_;
	public:
		BitIntSetException(int code, const std::string& message): error_code_(code), reason_(message) {}
		int code() const { return error_code_; }
		const std::string& message() const { return reason_; }

		friend std::ostream& operator<<(std::ostream& os, const BitIntSetException& e);
};
