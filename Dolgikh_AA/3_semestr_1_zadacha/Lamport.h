#include <string>

class Lamport {
	private:
		int N_;
		int K_;
		int *clock_;
	
	public:
		Lamport(int N, int K);
		~Lamport();
		bool operator <(const Lamport &right);
		Lamport operator =(const Lamport &right);
		friend std::ostream& operator<<(std::ostream &os, const Lamport &a);
		void step();
		void send(Lamport &receiver);
};

class Exception {
	private:
		int code_;
		std::string message_;
	public:
		Exception(int code, std::string message) : code_(code), message_(message) {}
		std::string message() const {return message_;}
		int code() const {return code_;}
};
