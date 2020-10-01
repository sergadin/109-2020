
#include "quant.hpp"

Quant::Quant(int left, int right)
{
    if(left - right == 0) {
    throw QuantError(-1, std::string("нулевой размер множества"));
}

    int max_size = abs(right-left);
    elements_ = new int[max_size];
    left_ = left;
    right_=right;
    n_ = 0;
}



Quant::~Quant()
{
    delete[] elements_;
}


void Quant::shift_left(int num)
{
    if (is_empty())
        return;
    for  (int k  = num + 1; k < n_;k++)
    {
        elements_[k-1] = elements_[k];
    }
    --n_;
}


void Quant::delete_item(int item)
{
    if (is_empty())
        throw QuantError(-4, std::string("тут пусто"));
    
    for(int i=0;i<abs(right_-left_);i++)
    {
        if (item==elements_[i])
        delete  &elements_[i];
        shift_left(i);
    }
    
}


void Quant::put_item(int item)
{
    if (is_full())
        throw QuantError(-2, std::string("место занято"));
    elements_[n_++] = item;
}

void Quant::clear()
{
    n_ = 0;
}

int Quant::quantity()
{
    return n_;
}

int Quant::min()
{
    int min = elements_[0];
    for(int i=0;i<abs(right_-left_);i++)
    {
        if (elements_[i] < min) min = elements_[i];
    }
    return min;
}


int Quant::max()
{
    int max = elements_[0];
    for(int i=0;i<abs(right_-left_);i++)
    {
        if (elements_[i] > max) max = elements_[i];
    }
    return max;
}

int Quant::left()
{
    return left_;
}
int Quant::right()
{
    return right_;
}

Quant & Quant::operator=(const Quant & right)
{
    if(this == &right) {return *this;}
    delete[] elements_;
    right_ =right.right_;
    left_ =right.left_;
    elements_= new int[abs(right_-left_)];
    
    for (int k=0; k < abs(right_-left_);k++)
        elements_[k] = right.elements_[k];
    n_ = right.n_;
    return *this;
}

Quant & Quant::operator==(const Quant & right)
{
    if(this == &right) {std::cout<<"равны";}
    else {std::cout<<"не равны";}
    return *this;
}

//Quant & operator+= (Quant &left, const Quant& right)
//{
 //   return left;
//}

std::ostream & operator<<(std::ostream &os, const Quant &q)
{
    os << "Quant of size " << abs(q.right_-q.left_)<<"with"<< q.n_ << "items";
    for (int k  = 0; k < q.n_;k++)
    {
       os << "\t" << q.elements_[k] << "\n";
    }
    return os;
}
