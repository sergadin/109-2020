class IntSet {
	private:
		int sup_;
		int inf_;
		int* list_;
		int size_;
		int len_;
		IntSet();
	public:
		IntSet(int min, int max);
		IntSet(const IntSet& set);
		~IntSet();

		bool is_empty() { return len_ == 0; }
		int length() { return len_; }

		void add_element(int a);
		void remove_element(int a);

		int min();
		int max();

		int left() { return inf_; }
		int right() { return sup_; }

		friend bool operator==(IntSet A, IntSet B);
		friend IntSet& operator*(IntSet A, IntSet B);
		IntSet& operator*=(IntSet B);
		IntSet& operator=(IntSet B);
}

class IntSetException {
	private:
		const int error_code_;
		const std::string reason_;
	public:
		IntSetException(int code, const std::string& message): error_code_(code), reason_(message) {}
		const std::string& message() const { return reason_; }
		int code() const { return error_code_; }
}
