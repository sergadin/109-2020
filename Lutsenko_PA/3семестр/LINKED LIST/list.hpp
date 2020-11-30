
#include <iostream>
template <typename T>



class List

{ private:
    class Error
    {   private:
        int code_;
        std::string reason_;
        
    public:
        Error(int code, const std::string& reason)
        {
            code_ = code;
            reason_ = reason;
        }
    };
    
    class ListItem
    {
    public:
        T data;
        ListItem *next;
    };
    
    ListItem *base_ = NULL;
    
    ListItem *current_ = NULL;
    
    int quant = 0;
    
    ListItem* prev(ListItem* item)
    {
        if ( (is_empty()) | (item == base_) )
        {
            throw Error(3, std::string("нет предыдущего"));}
        go_first();
        
        while ((current_->next != item)&(current_->next != NULL))
            go_next();
        return current_;
    }
    
public:
    
    class Iterator
    {
        ListItem *current_;
        
    public:
        void go_first();
        void go_next();
        T get_current();
        void set_current(T item);
        // bool is_valid();
    
    };
    
    
    bool is_empty()  //пустота списка РАБОТАЕТ
    {
        return (base_== NULL );
    }
    
    
   void add_first(T item) //добавить в начало  РАБОТАЕТ
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = base_;
        base_ = new_element;
        go_first();
        quant ++;
    }
    
    void construct(T item) //добавить в список после текущего   РАБОТАЕТ
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        if (is_empty())
           {
               new_element->next = NULL;
               base_ =  new_element;
               go_first();
               quant ++;
           }
        else { add_after(item);}
    }
  
    void add_after(T item) //добавить в список после текущего РАБОТАЕТ РАБОТАЕТ С ОШИБКАМИ ПРИ ВЫЗОВКЕ +
    {
       
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = current_->next;
        current_->next= new_element;
        go_next();
        quant ++;
    }
  
    
   void delete_first() //удалить первый РАБОТАЕТ 
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));} 
       ListItem *temp;
          temp = base_;
        base_= base_->next;
        delete temp;
        quant --;
    }
  
    void delete_after() //удалить из списка следующий РАБОТАЕТ
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        if (current_ == base_)
        {
            delete_first();
        }
      if  ((current_->next->next != NULL)&(current_->next != NULL))
      {  current_->next = current_->next->next;
         delete current_->next;
      }
        
    }
    void delete_this() //удалить из списка текущий  РАБОТАЕТ
       {
           if (is_empty()) {throw Error(2, std::string("список  пуст"));}
           if (current_ == base_)
           {
               delete_first();
           }
           current_ = prev(current_);
           delete_after();
       }
    
    void delete_list() // очистить список РАБОТАЕТ С ОШИБКАМИ
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        else{  go_first();
              for (int i = 0;i < quant -2 ; i++)
              {
                  delete_first();
              }
            quant = 0;
            base_ = NULL;}
    }
    
    ListItem* get_last() //получить последний элемент списка РАБОТАЕТ
    {
        go_first();
        while (current_->next != NULL)
            go_next();
        return current_;
    }
    
   int elem_count() //число элементов в списке РАБОТАЕТ
    {   /*ListItem * save_current = current_;
        if (is_empty()) {return 0;}
        go_first();
        int count = 1;
        while (current_->next != NULL)
        {
            count++;
            go_next();
        }
        current_ = save_current;
        return count;*/
        return quant - 1;
    }
    
    void print() // печать списка  РАБОТАЕТ
    
    {   ListItem * save_current = current_;
        
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        
        go_first();
  
        for (int i = 0;i < quant -1 ; i++)
        {
            std::cout << current_->data << " ";
                       go_next();
        }
        std::cout << std::endl;
        current_ = save_current;
    }

    void sort() // ака пузырьковая сортировка
    {
        ListItem * save_current = current_;
        
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
       
        for(int i = 0; i < quant -2; ++i)
        {      go_first();
               go_next();
            for(int r = 0; i < quant -2 - i -1; r++)
            {
                if(current_-> data > prev(current_)->data)
                {
                   
                   T temp = current_-> data;
                    current_-> data = prev(current_)->data;
                    current_-> next -> data = temp;
                }
                go_next();
            }
        }
         current_ = save_current;
    }
    
    List operator+ ( List & left) // НЕ РАБОТАЕТ НО ЧТО-то ВЫВОДИт
     {
        
      //  if ((! left.is_empty()) & (! (*this).is_empty()))
       //   {
            ListItem * save_currentl = left.current_;
            ListItem * save_currentt = (*this).current_;
            
            left.current_= left.get_last();
           (*this).current_= (*this).base_;
           int count = (*this).elem_count();
            while ( count > 1)
              {
                  left.add_after((*this).current_->data);
                  left.go_next();
                  (*this).go_next();
                  count--;
              }
         left.current_ = save_currentl;
         (*this).current_ = save_currentt;
             return   left;
     
          // }
   //     else {  if (left.is_empty()) return *this;
     //          if ((*this).is_empty()) return left;}
     }
     
    
    friend  bool operator==(  List & left,  List & right) //РАБОТАЕТ
       {   int left_quant =left.elem_count();
           int right_quant =right.elem_count();
           if (left_quant != right_quant) return 0;
           
           ListItem* r = right.base_;
           ListItem* l = left.base_;
           int k=0;
           for (int i=1;i <= left_quant ;i++)
           {
               if( r == l) k++;
               r = r->next;
               l = l->next;
           }
           if ( k ==  left_quant ) return 0; else return 0;
       }
    
    
    List operator=( List &old){ // РАБОТАЕТ
        
        if (old.base_ == NULL) {throw Error(2, std::string("список  пуст"));}
        
        else{
            
            this->~List();
            ListItem *prev, *last;
            prev = old.base_;
            last = new ListItem;
            last->data = prev->data;
            base_ = last;
            ListItem *temp;
            while(prev != NULL)
            {
                temp = new ListItem;
                temp->data = prev->data;
                last->next = temp;
                last = last->next;
                prev = prev->next;
            }
        }
        delete_first();
        return *this;
    }
    
    
    
    
    void go_first() { current_ = base_; }
    void go_next()  { current_ = current_->next; }
    void go_back() {prev(current_);}
    T get_current() {return current_->data;}
    void set_current (T item)
    {
          go_first();
          while (current_->data != item)
          go_next();
    }
    
    
};
