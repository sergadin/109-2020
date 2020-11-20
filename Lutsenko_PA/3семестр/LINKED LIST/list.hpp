
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
    
    ListItem *current_;
    
    
    ListItem* prev(ListItem* item)
    {
        if ( (is_empty()) | (item == base_) )
        {
            throw Error(3, std::string("нет предыдущего"));}
        go_first();
        
        while (current_->next != item)
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
    
    
    bool is_empty()  //пустота списка
    {
        return (base_== NULL );
    }
    
    
   void add_first(T item) //добавить в начало
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = base_;
        base_ = new_element;
        go_first();
    }
    
    void construct(T item) //добавить в список после текущего
    {
        ListItem *new_element = new ListItem;
        new_element->data = item;
        if (is_empty())
           {
               new_element->next = NULL;
               base_ =  new_element;
               go_first();
           }
        else { add_after(item);}
    }
  
    void add_after(T item) //добавить в список после текущего
    {
       
        ListItem *new_element = new ListItem;
        new_element->data = item;
        new_element->next = current_->next;
        current_->next= new_element;
        go_next();
        
    }
    
   void delete_first() //удалить первый
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
       ListItem *temp;
          temp = base_;
        base_= base_->next;
        delete temp;
    }
  
    void delete_this() //удалить из списка текущий
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        if (current_ == base_)
        {
            delete_first();
        }
        ListItem *temp;
        temp = current_;
        ListItem* prevv = prev(current_);
        prevv->next = current_->next;
        go_next();
        
    }
    
    void delete_list() // очистить список
    {
        if (is_empty()) {throw Error(2, std::string("список  пуст"));}
     
        while ((base_ != NULL)| ! (is_empty()))
        {
            delete_first();
        }
    }
    
    ListItem* get_last() //получить последний элемент списка
    {
        go_first();
        while (current_->next != NULL)
            go_next();
        return current_;
    }
    
    int elem_count() //число элементов в списке
    {
        if (is_empty()) {return 0;}
        go_first();
        int count = 1;
        while (current_->next != NULL)
        {
            count++;
            go_next();
        }
        return count;
    }
    
    void print() // печать списка
    
    {
       if (is_empty()) {throw Error(2, std::string("список  пуст"));}
        
        go_first();
        while (current_ != NULL)
        {
            std::cout << current_->data << " ";
            go_next();
        }
        std::cout << std::endl;
    }
    
    
    
       List operator+ (const List & left)
     {
     if (left.is_empty()) return & *this;
     if ((*this).is_empty()) return & left;
     if (! left.is_empty() | ! (*this).is_empty())
     {
     ListItem* r = (*this).base_;
     ListItem* l = left.get_last();
     
     while (r->next != NULL)
     {
     current_= l;
     left.add_after(r);
     (*this).delete_first();
     ListItem* r = (*this).base_;
     }
     return & left;
     
     }
     }
     
    
    
    
    friend  bool operator==( const List & left, const List & right)
    {
        if (left.elem_count() != right.elem_count()) return 0;
        ListItem* r = right.base_;
        ListItem* l = left.base_;
        int k=0;
        for (int i=1;i++;i == left.elem_count())
        {
            if( r == l) k++;
            r = r->next;
            l = l->next;
        }
        if ( k == left.elem_count() ) return 1; else return 0;
    }
    
    
    List operator=(const List &old){
        
        if (old.is_empty()) {throw Error(2, std::string("список  пуст"));}
        
        else{
            
            this->~List();
            ListItem *old, *last;
            old = *old->base_;
            last = new ListItem(old->data);
            base_ = last;
            ListItem *temp;
            while(old != NULL)
            {
                temp = new ListItem(old->data);
                last->next = temp;
                last = last->next;
                old = old->next;
            }
        }
        return *this;
    }
    
    
    
    
    void go_first() { current_ = base_; }
    void go_next()  { current_ = current_->next; }
    T get_current() {  return current_->data; }
    void set_current (T item)
    {
          go_first();
          while (current_->data != item)
            go_next();
    }
    
    
};
