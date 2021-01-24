#pragma once
#include <iostream>
#include "exception.h"

using namespace std;

template<class T>
class DeqList;

template<class T>
class Iterator
{
    friend class DeqList<T>;

private:
    DeqList<T> *List;
    typename DeqList<T>::ListNode *CurrentNode;

public:
    Iterator(const Iterator &i) 
    {
        List = i.List; 
	    CurrentNode = i.CurrentNode;
    }
    Iterator(DeqList<T> *p = nullptr, typename DeqList<T>::ListNode *pos = nullptr) 
    {
	    List = p;
	    CurrentNode = pos;
    }

///////////////////

    void operator=(const Iterator &i)
    {
	    List = i.List;
	    CurrentNode = i.CurrentNode;
    }
    bool operator!=(const Iterator &i)
    {
	    return (List != i.List) || (CurrentNode != i.CurrentNode);
    }
    bool operator==(const Iterator &i)
    {
	    return (List == i.List) && (CurrentNode == i.CurrentNode);
    }
    Iterator &operator++()
    {
        CurrentNode = CurrentNode -> next;
        return *this;
    }
    Iterator &operator--()
    {
        CurrentNode = CurrentNode -> prev;
        return *this;
    }
    T &operator*()
    {
	    return CurrentNode -> value;
    }
};

template<class T>
class DeqList
{
    friend class Iterator<T>;
private:
    struct ListNode
    {
        T value;
        ListNode *prev;
        ListNode *next;
        ListNode()
	{
	    next = this;
        prev = this;
	}
        void LinkNext(ListNode *p)
        {
	        next = p;
            p->prev = this;
	}
        void LinkPrev(ListNode *p) 
	    {
    	    prev = p; 
	        p->next = this;
        }
    };
    ListNode *head;
    int Size;

public:
    DeqList()
    {
        try{
            head = new ListNode;
            Size = 1;
        }
        catch (const bad_alloc &e){
            throw new MyException("DeqList<T>: memory allocation error\n", EC_MEMORY);
        }
    }
    DeqList(const T &x)
    {
        try{
            head = new ListNode;
            head->value = x;
            Size = 1;
        }
        catch (const bad_alloc &e)
        {
            throw new MyException("DeqList<T>: memory allocation error\n", EC_MEMORY);
        }
    }
    DeqList(const DeqList &L)
    {
	    head = L.head;
	    Size = L.Size;
    }


    ~DeqList()
    {
        Iterator<T> i(this, head->next);
        while (i.CurrentNode != head) DelForAfter(i);
        delete head;
    }

    void InsAfter(Iterator<T> &i, T &x);
    void InsBefore(Iterator<T> &i, T &x);

    bool DelForAfter(Iterator<T> &i);
    bool DelForBefore(Iterator<T> &i);

    Iterator<T> Head() 
    {
	    return Iterator<T>(this, head);
    }

    int GetSize() const {return Size;}

    void operator=(DeqList<T> &L)
    {
        Iterator<T> i = Head();
        Iterator<T> j = L.Head();
        do
        {
            i.CurrentNode->value = j.CurrentNode->value;
            ++i;
            ++j;
            cout << "R";
            //cout << *this;
        } while (i != Head() && j != L.Head());

        while (i != Head())
        {
            DelForAfter(i);
            cout << "T";
        }
        while (j != L.Head())
        {
            InsBefore(i, j.CurrentNode->value);
            ++j;
            cout << "Y";
            //cout << *this;
            cout << j.CurrentNode->value;
  
        }
        cout << "W" << L;
        cout << *this;
    }

    template<class P>
    friend ostream &operator<<(ostream& os, const DeqList<P> &L);
};



template<class T>
ostream &operator<<(ostream& os, const DeqList<T> &L)
{
    typename DeqList<T>::ListNode *p;
    cout << "[" << L.GetSize() << "] ";
    for (p  = L.head; p->next != L.head; p = p->next)
    {
	    cout << p->value << " ";
    }
    cout << p->value << endl;
    return os;
}

template<class T>
void  DeqList<T>::InsAfter(Iterator<T> &i, T &x)
{
    try
    {
        ListNode *p = new ListNode;
        //cout << "C" << x;
        p->value = x;
        //cout << "C" << x;
        p->LinkNext(i.CurrentNode->next);
        p->LinkPrev(i.CurrentNode);
        ++Size;
        //cout << "B" << p->value;
    }
    catch (const bad_alloc &e)
    {
        throw new MyException("DeqList<T>::InsAfter: memory allocation error\n", EC_MEMORY);
    }
}

template<class T>
void  DeqList<T>::InsBefore(Iterator<T> &i, T &x)
{
    try
    {
        ListNode *p = new ListNode;
        p->value = x;
        p->LinkPrev(i.CurrentNode->prev);
        p->LinkNext(i.CurrentNode);
        ++Size;
    }
    catch (const bad_alloc &e)
    {
        throw new MyException("DeqList<T>::InsAfter: memory allocation error\n", EC_MEMORY);
    }
}

template<class T>
bool DeqList<T>::DelForAfter(Iterator<T> &i)
{
    if (Size == 1) 
	    return 0;
    if (i.CurrentNode == head) 
	head = i.CurrentNode->next;
    ListNode *p = i.CurrentNode;
    i.CurrentNode = i.CurrentNode->next;
    i.CurrentNode->LinkPrev(p->prev);
    delete p;
    --Size;
    return 1;
}

template<class T>
bool DeqList<T>::DelForBefore(Iterator<T> &i)
{
    if (Size == 0) 
	    return 0;
    if (i.CurrentNode == head) 
	head = i.CurrentNode->prev;
    ListNode *p = i.CurrentNode;
    i.CurrentNode = i.CurrentNode->prev;
    i.CurrentNode->LinkNext(p->next);
    delete p;
    --Size;
    return 1;
}
