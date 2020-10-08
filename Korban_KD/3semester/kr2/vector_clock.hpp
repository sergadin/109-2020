class vector_clock
{
    private:
        int *clock_;
        int n_;
        int id_;
        
        vector_clock();
    public:
        vector_clock(int n , int id);
        
        ~vector_clock)();
        
        void local_add(int k = 1)
        { clock_[this->id_]++; }
        
        vector_clock & receve(const vector_clock & second);
    
        
        friend bool operator<(const vector_clock & left,const vector_clock & right);
        friend std::ostream& operator<< (std::ostream &,const vector_clock & a);
};

class vector_clock_Exception
{
    private:
        int code_;
        std::string cause_;
    public:
        vector_clock_Exception(int code, const std::string& message): code_(code), cause(message) {}
        const std::string& message() const { return cause_; }
        int code() const { return code_; }
};
