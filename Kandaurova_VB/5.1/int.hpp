typedef enum {I_OK = 0, I_SAME, I_FEW} ErrorCode;

class inte{
    private: 
        double *x;
        double *y;
        int N;
        ErrorCode *perr;
    public: 
        inte(double *a, double *b, int m, ErrorCode *perr);
        ~inte();
        double Y(double X, ErrorCode *perr);
};
