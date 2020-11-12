#include <iostream>

using namespace std;

class iterator_1;

class IntArray{
	private:
	int *arr_;
	int n_;
	public:
	IntArray(int n = 1);
	~IntArray();
	IntArray(const IntArray &other);
	int get_elem(int i) const;
	void set_elem(int i, int cmp);
	void del_elem(int i);
	int find_elem(int cmp) const;
	IntArray& operator=(const IntArray &other);
	friend class iterator_1;
	iterator_1 begin();
	friend std::ostream& operator<<(std::ostream &os, const IntArray& array);
};

class iterator_1{
	private:
	IntArray *array_;
	int pos_;
	public:
	iterator_1(int pos, IntArray *array);
	~iterator_1();
	bool check_bound();
	int get_cmp();
	void step();
	iterator_1& operator=(const iterator_1 &other);
	friend class IntArray;
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
