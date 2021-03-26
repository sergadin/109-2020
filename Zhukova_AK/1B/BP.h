
#include <iostream>
#include <string>
//#include <cstdio>

class BonusProgram
{
        private:
                int n; //размер массива m1, m2
                int *m1, *m2; //m1 - кол-во совершённых операций
                //m2 - сумма потраченных средств

                std::string program;
        public:
                BonusProgram (int l,const  std::string & program);
                BonusProgram (const BonusProgram& v);
                ~BonusProgram();
                void Registration (int coordinate, int sum);
                BonusProgram operator = (const BonusProgram &other);
                BonusProgram operator + (const BonusProgram &other);
                bool operator < (const BonusProgram &other);
                void print_program () const;

};

class BonusProgramException
{
        private:
                int code_;
                std::string message_;
        public:
                BonusProgramException(int code, const std::string& message) : code_(code), message_(message) {}
                const std::string& message() const { return message_; }
                int code() const { return code_; }
};




