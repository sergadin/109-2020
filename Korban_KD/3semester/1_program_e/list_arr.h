#ifndef list_arr_H
#define list_arr_H

template <typename T>
class list_arr 
{
private:
    class node 
    {
    public:
        T *data_ = nullptr;
        node *next_ = nullptr, *prev_ = nullptr;
        node(size_t size_of_arr)
        {
            data_ = new T[size_of_arr];
            next_ = nullptr;
            prev_ = nullptr;
        }
        node(size_t size_of_arr,node* new_next, node* new_prev)
        {
            data_ = new T[size_of_arr];
            next_ = new_next;
            prev_ = new_prev;
        }
        node(T *new_data,size_t new_len_arr, node* new_next, node* new_prev) : next_(new_next), prev_(new_prev) 
        {
            data_ = new T[new_len_arr];
            
            for(int i = 0; i < new_len_arr; i++)
            {
                data_[i] = new_data[i];
            }
        }
        ~node()
        {
            printf("dest_node\n");
            delete[] data_;
        }
    };
    node *head_ = nullptr;
    node *tail_ = nullptr;
    
    size_t mem_size_ = 0;
    size_t real_size_ = 0;
    size_t len_arr_ = 10;
    
public:
    list_arr();
    list_arr(size_t len);
    list_arr(const list_arr<T> & that);
    list_arr(list_arr<T> && that);
    list_arr<T> & operator = (const list_arr<T> & that);
    list_arr<T> & operator = (list_arr<T> && that);
    ~list_arr();
    
    void pop_back();
    void pop_front();
    void clear();
    void expand(size_t expd_size);
    
    size_t size() const;
    bool empty() const;

    T * front();
    T const& front() const;

    T * back();
    T const& back() const;

    
    
    T& operator[] (const size_t idx);
    T const& operator[] (const size_t idx) const;
    
    /*
    typedef T* iterator;
    typedef T* const const_iterator;

    const_iterator begin() const; // cbegin
    iterator begin();

    const_iterator end() const; //cend()
    iterator end();

    const_iterator rbegin() const;
    iterator rbegin();

    const_iterator rend() const;
    iterator rend();
    */
    enum ERRORS
    {
        EMPTY = -10,
        INDEX_ERR
    };
    
};

class list_arr_exception
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		list_arr_exception(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};



#endif 
