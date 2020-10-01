class IntSet {
	private:
		const int sup_;
		const int inf_;
		int* list_;
		int size_;
		int len_;
		IntSet();
	public:
		IntSet(int min, int max);
		IntSet(const IntSet& set);
		~IntSet();

		bool is_empty() const { return len_ == 0; }
		int len() const { return len_; }

		void add_element(int a);
		void remove_element(int a);

		int min() const;
		int max() const;

		int left() const { return inf_; }
		int right() const { return sup_; }

		friend bool operator<=(const IntSet& A, const IntSet& B);
		friend bool operator==(const IntSet& A, const IntSet& B);
		friend IntSet operator*(const IntSet& A, const IntSet& B);
		IntSet& operator*=(const IntSet& B);
		IntSet& operator=(const IntSet& B);
};

class IntSetException {
	private:
		const int error_code_;
		const std::string reason_;
	public:
		IntSetException(int code, const std::string& message): error_code_(code), reason_(message) {}
		const std::string& message() const { return reason_; }
		int code() const { return error_code_; }
};
