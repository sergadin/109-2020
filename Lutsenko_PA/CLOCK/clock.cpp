#include "clock.hpp"


VClock::VClock(int n,int k)
{
    
    n_ = n;
    k_ = k;
    if(k_ <= 0) {
        throw VClockError(-2, std::string("плохо дело"));
    }
    if(n_ <= k_) {
        throw VClockError(-2, std::string("не хватает ячеек времени"));
    }
    if(n_ <= 0) {
        throw VClockError(-1, std::string("нулевой размер  векторa"));
    
  
}
    
    coordinates_ = new int[n];
    coordinates_[0] = k_;
    for  (int i = 1; i < n ; i++)
    {
        coordinates_[i] = 0; // хануляем вектор
    }
 
}



VClock::~VClock()
{
    delete[] coordinates_;
}


void operator==( const VClock & left, const VClock & right)
{
    if ( left.n_ != right.n_ )
        throw VClockError(-3, std::string("вектора разных размеров не сравнимы"));
    int sravnimost = 0;
    
    for (int i = 1; i < left.n_ ; i++)
    {
        if (left.coordinates_[i] >= right.coordinates_[i])
            if (left.coordinates_[i] > right.coordinates_[i]) sravnimost ++;
    }
    
    if (sravnimost > 0 ) { std::cout<<"событие с номером "<< left.coordinates_[0]<< " произошло позже события с номером "<<right.coordinates_[0]<<std::endl;}
    
    if (sravnimost == 0) { std::cout<<"событие с номером "<< right.coordinates_[0]<< " не сравнимо с событием номера "<<left.coordinates_[0]<<std::endl;}
    
}


void VClock::PrintCoordinates()
{   std::cout<<"коррдинаты вектораc с номером "<< coordinates_[0] <<std::endl;
    for (int i = 1; i < n_ ; i++)
    {
        std::cout<<coordinates_[i]<<"," ;
    }
    std::cout<<std::endl;
}

void VClock::Local()
{
    coordinates_[coordinates_[0]] ++;
   
}

VClock & VClock:: operator=(const VClock & right)
{
  
   
    n_ =right.n_;
    coordinates_= new int[n_];
    
    for (int i=0; i < n_;i++)
     coordinates_[i] = right.coordinates_[i];

   return *this;
}

void VClock::Global (const VClock & m)
{
    coordinates_[coordinates_[0]] ++;
    for (int i = 1; i < n_ ; i++)
    {
        if (i != coordinates_[0] )
      {
          if (coordinates_[i] < m.coordinates_[i]) coordinates_[i] = m.coordinates_[i];
      }
        
    }
   
    
}



