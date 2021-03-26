
#include <string>
#include <cstdio>
#include <math.h>
#include <iostream>

using namespace std; 

class listException
{
    private:
        int code_;
        std::string reason_;
    public:
        listException(int code, const std::string& reason)
        {
            code_ = code;
            reason_ = reason;
        }

        const std::string& get_reason() const
        {
            return reason_;
        }

};

template <typename T> 
class list 
    {
    struct list_element 
        {
        T data;
        list_element *next; 
        list_element *prev; 
        };
        
        private: 
        list_element *head; 
        list_element *curr; 

        public:
        int length;
        class Iterator
        {
            private:
                friend class list<T>;
                friend class list_element;
                list_element *cur_;

            public:
                Iterator()
                {
                    cur_= nullptr;
                }
                friend bool operator !=(const Iterator& left, const Iterator& right)
                {
                    if(left.cur_ != right.cur_)
                        return true;
                    else
                        return false;
                }

                void inext(Iterator & i)
                                {
                                        i.cur_ = i.cur_->next;
                                }
                void iprev(Iterator & i)
                                {
                                        i.cur_ = i.cur_->prev;
                                }
                T get_it(const Iterator & i)
                                {
                                        return i.cur_->data;
                                }


                Iterator& operator= (const Iterator & right)
                {
                    cur_ = right.cur_;
                    return *this;
                }



        };
 


list() 
    {
      head =NULL;
      curr=NULL; 
      length=0; // обнуляем все что есть
    }


list(const list<T> &C) // конструктор копий	
      {
      this->head=NULL; 
      this->curr=NULL; 
      this->length=0; // обнулям
      list_element *p=C.curr;	 
      for(int i=0; i<C.length; i++) 
		{ 
			add(p->data);
			p=p->next; 
		}
        }
 
~list() 
	{
        clear(); 
	}

Iterator begin()
        {
            Iterator i;
            i.cur_ = head;
            i.inext(i);
            return i;
        }
Iterator end()
    {
        Iterator i;
        i.cur_ = head;
        i.inext(i);
        while(i.cur_ != head)
        {
            i.cur_ = i.cur_->next;
            if(i.cur_->next == nullptr)
                break;
        }
        return i;
}

void next() 
	{
	  if(isNoEmpty()) 
			curr=curr->next; 
	}

void prev() 
	{
	if(isNoEmpty()) 
			curr=curr->prev; 
	}

int isNoEmpty() 
	{
	  if (curr==NULL ) 
    {
			return 0;
    } 
	  else {
			return 1; 
      }
	}



T getValue() //  получениe значения текущего элемента
	{

	  if(isNoEmpty()) 
			return curr->data; 
	  else 
			throw listException(-2, std::string("error")); 
	}

void add(T data)	// добавлениe элемента
	{
    list_element *ins; 
    ins= new list_element;	
    ins->data=data; 
    if (!isNoEmpty()) 
    {
        head=ins; 
        curr=ins; 
        curr->next=ins; 
        curr->prev=ins; 
    }
    else 
    {
        ins->next=curr->next; 
        ins->next->prev=ins;	
        curr->next=ins;  
        ins->prev=curr;  
    }
    length++;
    curr=ins; 
}

void print() 
{
    if (isNoEmpty()) 
	{
        list_element *temp=head; 
        for (int i=0; i<length; i++)
		{ 
		std::cout << temp->data <<" "; 
		temp=temp->next ; 
		} 
		std::cout << "\n"; 
    }

    else 
    {
        std::cout<< "list is empty\n" ; 
    }
}


void clear() // чистим списочек
{
    for (int i=0; i<length; i++) 
		extract();
}
 

void sort() //сортировкa списка
{
 T Temp; 
 int i,j;  
 for (j=0; j<length-1; j++) 
	{
		currToHead(); 									
		for(i=0; i<length-1; i++)	
		{
		if(curr->data > curr->next->data)  
			{ 
			Temp=extract(); 
			next(); 
			add(Temp);	
			}
		else 
			next(); 
		}
        i=0;  
	}
}

void currToHead()  
    {
      curr=head; 
    }

T extract() // извлечениe текущего элемента
{
    T t; 
    if (!isNoEmpty()) 
    return 0; 
    list_element *temp=curr; 
    t=temp->data;
    if (length==1) 
    {
        head=NULL; 
        curr=NULL; 
    }
    else 
        {
        curr->next->prev=curr->prev; 
        curr->prev->next=curr->next; 
        curr=curr->next; 
        }
    if(temp==head) 
        head=head->next;
        curr=head; 
    length--;  
    delete temp; 
    return t; 
}

    list<T>& operator=(const list<T>& right)//
    {
            list_element* p;
            clear();
            curr = head;
            p = right.head;
            add(p->data);
            p = p->next;
            while (p != right.head)
            {
                add(p->data); 
                p = p->next;
            }
            curr = head->next;
            p = nullptr;
            return *this;
     }

    
        friend std::ostream& operator<<(std::ostream &out, const list<T> &H)
        {
            list_element * p;
            p = H.head->next;
            while (p != H.head)
            {
                out << p->data << "\t";
                p = p->next;
            }
            p = nullptr;
            return out;
        }
    };


int main()
{
    try
    {  

        list<int> L;
        cout << "L"<< endl;
        L.print();
        cout << endl;

        list<string> S;
        cout << "S" << endl;
        S.add("mexmat ");
        S.add("kills ");
        S.print();
        cout << endl;

        list<int> K;
        cout << "K"<< endl;
        K.add(101);
        K.add(15);
        K.print();
        for(int i = 0; i < 10; i++)
        {
            K.extract();
        }
        K.print();
        cout << endl;

        list<int> S1;
        S1.add(3);
        S1.add(1);
        cout << "S1"<< endl;
        S1.print();

        list<int>::Iterator i;
        for(i = S1.begin(); i != S1.end(); i.inext(i))
        {
            cout<< i.get_it(i);
        }
        cout << endl;
        S1.sort();
        S1.print();
        cout << endl;

        list<int> V;
        V.add(7);
        V.add(15);
        V.add(1);
        cout << "V"<< endl;
        V.print();
        cout << endl;

        list<int> G;
        G = V;
        cout << "G" << endl;
        G.print();
        cout << endl;


        list<double> X; 
        X.add(1.333);
        cout << "X" << endl;
        X.print();
        cout << endl;

}
    catch(listException &err)
    {
        std::cout << err.get_reason() << std::endl;
    }
    return 0;
}
