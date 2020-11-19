
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

      ListItem base_;
      ListItem *current_;
      ListItem* prev(ListItem* item)
        {
          if ( (is_empty()) | (item == base_) )
          {
             throw Error(3, std::string("нет предыдущего"));}
             ListItem *p = base_;
             while (p->next != item)
             p = p->next;
             return p;
        }
    
      public:
    
        class Iterator
    {
        ListItem *current_;
        
        public:
        void go_first();
        void go_next();
        T get_current();
       // bool is_valid();
    };
        
        
   bool is_empty()  //пустота списка
      {
          return base_ == NULL;
      }
    
   void add_first(T item) //добавить в начало
    {
      ListItem *new_element = new ListItem;
      new_element->data = item;
      new_element->next = this->base_->next;
      base_ = item;
    }
    
    void add_after(T item) //добавить в список после текущего
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = this->current_->next;
        this->current_ = new_element;
        
        if (item == current_->data)
        {
           throw Error(1, std::string("добавляемый элемент совпалает с предыдущим"));
        }
    }
    
    void delete_first() //удалить первый
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        ListItem *temp;
        temp =base_;
        base_ = base_->next;
        delete temp;
    }
    
    void delete_this(ListItem *item) //удалить из списка
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        
        if (item == base_)
        {
            delete_first(item);
        }
        
        ListItem* prev = prev(item);
        prev->next = item->next;
        delete item;
    }
    
    void delete_list() // очистить список
    {
       if (is_empty()) {throw Error(2, std::string("список  пуст"));}
       while (base_ != NULL)
        {
            delete_first();
        }
    }
        
        ListItem* get_last()
         {
           ListItem* p = base_;
           while (Next(p) != NULL)
           p = p->next;
           return p;
         }
    
    void print() // печать списка
        
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
       
        ListItem *p = base_;
         while (p != NULL)
        {
          std::cout << p->date << " ";
          p = p->next;
        }
        std::cout << std::endl;
    };
     
        List operator+( const List & left, const List & right)
        {
            if (left.is_empty()) return & right;
            if (right.is_empty()) return & left;
            ListItem* r = right.base_;
            ListItem* l = left.get_last();
            
            while (r->next != NULL)
            {
                current_= l;
                left.add_after(r);
                right.delete_first();
                ListItem* r = right.base_;
            }
            return & left;
        }
        
    friend  bool operator==( const List & left, const List & right)
        {
            if (count.left != count.left) return 0;
            ListItem *p1 = *left.base_;
            ListItem *p2 = *right.base_;
            k=0;
            for (int i=1;i++;i==count.left)
            {
                if(p1 == p2)
        }
        
    /*
     List &List:: operator=(const List &old){
   
            if(this != &old){
                mySize = old.mySize;
                if(old.mySize == 0)
                    first = NULL;
      
                else{
                mySize = old.mySize;
                    this->~LinkedList();
                    ListItem *old, *last;
                   old = origList.first;
                    last = new ListItem(old->data);
                    first = last;
                    ListItem *temp;
                    while(old != NULL)
                    { //cycle through origList
                        temp = new Node(origPtr->data); //copy data in current node of origList
                        lastPtr->next = temp;  //add temp to end of this list
                        lastPtr = lastPtr->next; //advance lastPtr to end of this list
                        origPtr = origPtr->next; //go to next node in origList
                    }
                }
            }
            return *this;
        }
     */
    
   void go_first() { current_= base_; };
    void go_next()  { current_= current_->next; };
    T get_current() {  return current_->data; };
      
    
};

   
