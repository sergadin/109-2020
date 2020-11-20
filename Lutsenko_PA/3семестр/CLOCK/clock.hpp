#include <iostream>

class VClockError
{
    
private:
    int code_;
    std::string reason_;
    
public:
    VClockError(int code, const std::string& reason)
    {
        code_ = code;
        reason_ = reason;
    }
    
    const std::string& get_reason() const { return reason_; }
};
  class VClock

   {
   private:
       
       int *coordinates_;
       int n_;  // размерность
       int k_;  //
      
       VClock () {}
   public:
       
       VClock( int n_, int k_);
       
       ~VClock();
       //печать координат
       void PrintCoordinates();
       
      VClock & operator=(const VClock & right);
       //Сравнение двух меток.
       friend  void operator==( const VClock & left, const VClock & right); //Сравнение двух меток.
       // Подпись локального события.
       void Local();
       // Подпись события, соответсвующего получению сообщения с меткой m
       void Global(const VClock & m);
    
       
    
   };
