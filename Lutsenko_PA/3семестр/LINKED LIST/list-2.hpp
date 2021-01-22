
#include <iostream>



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

template <typename T>
class List

{ private:
   
    
    class ListItem
    {
    public:
        T data;
        ListItem *next;
    };
    
    ListItem *base_;
    
    ListItem *current_;
    
    int quant = 0;
    
    ListItem* prev(ListItem* item)
    {
        if ( (is_empty()) | (item == base_) )
        {
            throw Error(3, std::string("нет предыдущего"));
        }
         
        ListItem * save_current = current_;
        go_first();
        
        while ((current_->next != item) && (current_->next != NULL))
            go_next();
        return current_;
        current_ = save_current;
    }
    
public:

    List()
    {
        base_ = NULL;
        current_ = NULL;
    };

  /*  ~List()
    {
        delete_list();
    } */
    
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
    
    
    bool is_empty()  //пустота списка
    {
        return (base_== NULL);
    }
    
    
   void add_first(T item) //добавить в начало
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = base_;
        base_ = new_element;
        go_first();
        quant ++;
    }
    
    void add_item(T item) //добавить в список после текущего
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
        else
            {
                new_element->data = item;
                new_element->next = current_->next;
                current_->next= new_element;
                go_next();
                quant ++;
            }
    }
    
   void delete_first() //удалить первый
      {
          if (is_empty()) {throw Error(2, std::string("список  пуст"));}
         //   if (quant == 1) {base_ = NULL;}
          else{
          ListItem *temp;
              temp = base_;
              base_= base_->next;
              quant --;
              delete temp;
          }
          
      }
  
    void delete_after() //удалить из списка следующий
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        if (current_ == base_)
        {
            delete_first();
        }
      if( ( current_->next->next != NULL ) && ( current_->next != NULL ) )
      {  
        ListItem* newway = current_->next->next;
        delete current_->next;
        current_->next = newway; 
        quant --;
      }
        
    }
    void delete_this() //удалить из списка текущий
       {
           if (is_empty()) {throw Error(2, std::string("список  пуст"));}
           if (current_ == base_)
           {
               delete_first();
           }
           current_ = prev(current_);
           delete_after();
       }
    
    void delete_list() // очистить список
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
       
        else{
              go_first();
              
                while (!is_empty())
                { //std::cout <<quant << std::endl;
                delete_first();
                }
            
            quant = 0;
            base_ = NULL;}
    }
    
    ListItem* get_last() //получить последний элемент списка
    {
        go_first();
        while (current_->next != NULL)
            go_next();
        return current_;
    }
    
   int elem_count() //число элементов в списке
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
        return quant;
    }
    
    void print() // печать списка
    
    {   ListItem * save_current = current_;
        
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        
        go_first();
  
        for (int i = 0;i < quant  ; i++)
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
        
         int k = 1;
         while (k<=quant )
         {      go_first();
                
             for(int r = 0; r < quant - 1; r++)
             {
                 if(current_-> data < current_-> next -> data )
                 {
                    
                    T temp = current_-> data;
                     current_-> data = current_-> next -> data ;
                     current_-> next -> data = temp;
                 }
                 //if (current_-> next -> next != NULL) { go_next();}
                 go_next();
                 
             }
             k++;
         }
          current_ = save_current;
         
     }

    
   friend  List operator+ (  List  &left,  List  &right) //   this = правый
     {
        
      if ( left.is_empty() &&  right.is_empty())  {throw Error(4, std::string("списки пусты"));}
       
            ListItem * save_current_left = left.current_;
            ListItem * save_current_right = right.current_;
            
           left.current_= left.get_last();
           right.go_first();
           int k = 1;
           while (k <= right.quant )
              {
                  left.add_item(right.current_->data);
                  right.go_next();
                  
                  k++;
                 // left.print();
                  
              }
    
         left.current_ = save_current_left;
         right.current_ = save_current_right;
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
           
           if ( k ==  left_quant ) return 0; else return 1;
       }
    
    
    List operator=( List &old){ //
        
        if (old.base_ == NULL) {throw Error(2, std::string("список  пуст"));}
        
        else{
            
            this->~List();
          
            ListItem * save_current = old.current_;
            old.go_first();
            go_first();
            (*this).quant = 0;
            while (old.current_ != NULL)
            {
                add_item(old.current_->data);
                old.go_next();
                
            }
           delete_first();
            go_first();
            int razn = quant - old.quant;
            for (int i=1;i <old.quant ;i++) go_next();
            for (int i=0;i <razn ;i++) delete_after();
            (*this).quant = old.quant;
            current_ = save_current; 
        }
        
        
        return *this;
    }
    
    
    
  /*  void go_last()
    {
       // go_first();
      //  for (int i=1;i <quant ;i++)
        while(current_->next != NULL)
        go_next();
        
    } */
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
