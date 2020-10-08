#include <ostream>
#include <string>

class vector_clock
{
    private:
        int *clock_;
        int n_;
        int id_;
        
        vector_clock();
		vector_clock & operator=(const vector_clock & right);
    public:
        vector_clock(int n , int id);
        
        ~vector_clock();
		
		int get_id()
		{return id_; }
        
        void local_add(int k = 1)
        { clock_[id_]++; }
        
        vector_clock & receve(const vector_clock & second);
        
        friend bool operator<(const vector_clock & left,const vector_clock & right);
        friend std::ostream & operator<<(std::ostream &os ,const vector_clock & a);
};

class vector_clock_Exception
{
    private:
        int code_;
        std::string cause_;
    public:
        vector_clock_Exception(int code, const std::string& message): code_(code), cause_(message) {}
        const std::string& message() const { return cause_; }
        int code() const { return code_; }
};
