#include "vector_clock.hpp"

using namespace std;


vector_clock::vector_clock(int n , int id)
{
    if((n < 0)) 
    {
        throw vector_clock_Exception(-1, "incorrenct number of processes");
    }
    
    if(( id_ >= n )) 
    {
        throw vector_clock_Exception(-2, "incorrenct process id");
    }
	
	this->id_ = id;
    this->n_ = n;
    
    clock_ = new int[n];
    for(int i = 0; i < n_; i++)
        clock_[i] = 0;
}

vector_clock::~vector_clock()
{
    delete [] clock_;
}

vector_clock & vector_clock::receve(const vector_clock & second)
{
    if( this->n_ != second.n_ )
    {
        throw vector_clock_Exception(-3, "number of processes does not match");
    }
    
    if( this->id_ == second.id_ )
    {
        throw vector_clock_Exception(-4, "can not receve message from same process, use local_add");
    }
    
    if (this->clock_[id_] < second.clock_[id_])
    {
        throw vector_clock_Exception(-5, "process can not receve mesages from his future");
    }
    
    for(int i = 0; i < n_; i++)
    {
        if(this->clock_[i] < second.clock_[i] )
            this->clock_[i] = second.clock_[i];
    }
	this->local_add();
    return *this;
}

 bool operator<(const vector_clock & left,const vector_clock & right)
{
    if(left.id_ == right.id_)
        return false;
    
    if( left.n_ != right.n_ )
    {
        throw vector_clock_Exception(-3, "number of processes does not match");
    }
    
    for(int i = 0; i < left.n_; i++)
    {
        if( left.clock_[i] >= right.clock_[i] ) 
            return false;
    }
    return true;
    
}

std::ostream& operator<<(std::ostream &os,const vector_clock & a)
{
    os << "process: " << a.id_ << " state: (";
    for(int i = 0; i < a.n_ - 1; i++)
    {
        os << a.clock_[i] << ", ";
    }
    os << a.clock_[a.n_ - 1] << ")";
    return os;
}

