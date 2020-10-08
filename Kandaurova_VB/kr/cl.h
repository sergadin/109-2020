class cl{
    private:
        int n_;
        int k_;
        int *x_;
        cl();
    public:
        cl(int n, int k);
        ~cl();
        void send();//подпись локального события

        cl& receve(const cl& b);//подпись события

        friend bool operator<=(const cl& a, const cl& b);
        friend std::ostream& operator<< (std::ostream &,const cl& a);
};

class UserException {
	private:
		int code_;
		std::string message_;
	public:
		UserException(int code, const std::string& message) {
            code_ = code;
            message_ = message;
        }
		const std::string& get_reason() const { 
            return message_;
        }
		int code() const {
            return code_;
        }
};
