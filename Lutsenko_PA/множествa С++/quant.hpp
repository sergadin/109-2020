#include <iostream>

class QuantError {
private:
    int code_;
    std::string reason_;
    
public:
    QuantError(int code, const std::string& reason) {
        code_ = code;
        reason_ = reason;
    }
    
    const std::string& get_reason() const { return reason_; }
};
  class Quant

   {
   private:
       int *elements_;
       int left_;
       int right_;
       int n_;   // число элем в множесте текущее
      
       void shift_left(int num); //сдвиг влево
       Quant () {}
   public:
       // создание пустого множества с макс размером
       Quant( int left, int right);
       ~Quant();
       
   
       // добавить item в конец очереди
       void put_item(int item);
       // удалить item
       void delete_item(int item);
       
       
       bool is_empty() const
       {
           return n_ == 0;
           
       };
    
       bool is_full() const
       {
           return n_ == (abs(right_ - left_) - 1);
           
       };
       
       int min();
       int max();
       int left();
       int right();
       int quantity(); //количество элементов во множестве
      
       
       
       void clear();
       
       Quant & operator=(const Quant & right);// присваивание
       Quant & operator==(const Quant & right); //сравнение
       //friend Quant& operator+= (Quant &left, const Quant& right);
       friend std::ostream&  operator<<(std::ostream &os, const Quant& q);
   };
