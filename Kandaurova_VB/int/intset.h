class inte{
	private:
		int n;
		int left;
		int right;
		int *a;
	public:
		inte(int left, int right);//+
		~inte();//+
		inte(const inte &integer); //конструктор копирования
		inte& operator=(const inte &integer); //оператор присваивания
		inte& operator==(const inte &integer);
		int check() const; //+проверка пустоты множества
		int fmin() const;//+
		int fmax() const;//+
		int fleft() const;//+
		int fright() const;//+
		void print() const;
		void add(int x);//+
		void del(int x);//+

        friend inte& operator*(const inte &x, const inte &y);
        friend inte& operator*=(inte &x, const inte &y);
};


class InteError {
    private:
        int code_;
        std::string reason_;

    public:
        InteError(int code, const std::string& reason) {
            code_ = code;
            reason_ = reason;
        }

        const std::string& get_reason() const { return reason_; }
};
