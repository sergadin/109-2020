#include <iostream>
#include <string>

class error_vector_clock{
    private:
        int code_;
        std::string reason_;

    public:
        error_vector_clock(int code, const std::string& reason) {
            code_ = code;
            reason_ = reason;
        }

        const std::string& get_reason() const { return reason_; }
};

class vector_clock{
private:
    unsigned int dim_, index_;
    unsigned int *time_;
    vector_clock();
public:
    vector_clock(const unsigned int dim, const unsigned int index);
    ~vector_clock();
    void sign();
    void message(const vector_clock & x);
    void print_vector_clock();
    vector_clock & operator=(const vector_clock & x);
    friend bool operator < (const vector_clock &x, const vector_clock &y);
    friend std::ostream& operator<<(std::ostream &os, const vector_clock& q);
};
