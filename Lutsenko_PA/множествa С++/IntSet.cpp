
#include "IntSet.hpp"

IntSet::IntSet(int left, int right)
{
    if(left - right == 0) {
    throw IntSetError(-1, std::string("нулевой размер множества"));
}

    int max_size = abs(right-left);
    elements_ = new int[max_size];
    left_ = left;
    right_=right;
    n_ = 0;
}



IntSet::~IntSet()
{
    delete[] elements_;
}


void IntSet::shift_left(int num)
{
    if (is_empty())
        return;
    for  (int k  = num + 1; k < n_;k++)
    {
        elements_[k-1] = elements_[k];
    }
    --n_;
}


void IntSet::delete_item(int item)
{
    if (is_empty())
        throw IntSetError(-4, std::string("тут пусто"));
    
    for(int i=0;i<abs(right_-left_);i++)
    {
        if (item==elements_[i])
        delete  &elements_[i];
        shift_left(i);
    }
    
}


void IntSet::put_item(int item)
{
    if (is_full())
        throw IntSetError(-2, std::string("место занято"));
    elements_[n_++] = item;
}

void IntSet::clear()
{
    n_ = 0;
}

int IntSet::quantity()
{
    return n_;
}

int IntSet::min()
{
    if (is_empty())
    throw IntSetError(-4, std::string("тут пусто"));
    
    int min = elements_[1];
    for(int i=0;i<n_;i++)
    {
        if (elements_[i] < min) min = elements_[i];
    }
    return min;
}


int IntSet::max()
{
    if (is_empty())
    throw IntSetError(-4, std::string("тут пусто"));
    
    int max = elements_[1];
    for(int i=0;i<n_;i++)
    {
        if (elements_[i] > max) max = elements_[i];
    }
    return max;
}

int IntSet::left()
{
    return left_;
}
int IntSet::right()
{
    return right_;
}

IntSet & IntSet::operator=(const IntSet & right)
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

IntSet & IntSet::operator==(const IntSet & right)
{
    if(this == &right) {std::cout<<"равны";}
    else {std::cout<<"не равны";}
    return *this;
}

IntSet & IntSet::operator*=(const IntSet & right)
{
   if(this == &right) {return *this;}
    
    if (n_!=0)
    {
      for (int k=0; k < n_;k++)
         {  int match = 0;
           for (int p=0; p < n_;p++)
           if  (elements_[k] == right.elements_[p] ) match++;
           if (match==0)
        {
            delete  &elements_[k];
            shift_left(k);
           }
         }
    }
    else throw IntSetError(-5, std::string("множесьва не пересекаются"));

    return *this;
}

//IntSet & IntSet::operator*(const IntSet & right)
//{
 //   if(this == &right) {return *this;}
 //   int maximum;
//    if (n_>right.n_) maximum = n_ ; else maximum = right.n_;
//    int *massiv = new int [maximum];
//    int num=0;
//    {
 //       for (int k=0; k < n_;k++)
 //       {
//            for (int p=0; p < n_;p++)
//                if  (elements_[k] == right.elements_[p] )
 //                  {
 //                      massiv[num]= elements_[k];
  //                     num++;
 //                  }
 //           }
 //   }
//    if (num = 0) throw IntSetError(-5, std::string("множесьва не пересекаются"));
    
 //   return massiv;
//}
std::ostream & operator<<(std::ostream &os, const IntSet &q)
{
    os << "Quant of size " << abs(q.right_-q.left_)<<"with "<< q.n_ << "items ";
    for (int k  = 0; k < q.n_;k++)
    {
       os << "\t" << q.elements_[k] << "\n";
    }
    return os;
}
