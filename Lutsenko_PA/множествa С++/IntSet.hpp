#include <iostream>

class IntSetError {
private:
    int code_;
    std::string reason_;
    
public:
    IntSetError(int code, const std::string& reason) {
        code_ = code;
        reason_ = reason;
    }
    
    const std::string& get_reason() const { return reason_; }
};
  class IntSet

   {
   private:
       int *elements_;
       int left_;
       int right_;
       int n_;   // число элем в множесте текущее
      
       void shift_left(int num); //сдвиг влево
       IntSet () {}
   public:
       // создание пустого множества с макс размером
      IntSet( int left, int right);
       ~IntSet();
       
   
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
       
       IntSet & operator=(const IntSet & right);// присваивание
       IntSet & operator==(const IntSet & right); //сравнение
  //     IntSet & operator*(const IntSet & right); // пересечения
     IntSet & operator*=(const IntSet & right);
       
       friend std::ostream&  operator<<(std::ostream &os, const IntSet& q);
   };
