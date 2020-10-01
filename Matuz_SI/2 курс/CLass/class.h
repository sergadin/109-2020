#include <iostream>
using namespace std;


class UserException {
private:
    int code_;
    string message_;
public:
    UserException(int code, string message);
    string message() const;
    int code() const;
};

class limited_int {
private:
    int min_;
    int max_;
    int size_;
    int *data_;

    bool is_there(int element) const;
    void order_data();
    limited_int();

public:
    limited_int(int min, int max);
    ~limited_int();

    int left() const;
    int right() const;

    int getmin() const;
    int getmax() const;

    int how_many() const;
    bool is_empty() const;

    void put_element(int element);
    void delete_element(int element);

    /* И что с ними делать...
    limited_int& operator= (const limited_int & right);
    friend limited_int& operator* (const limited_int &right, const limited_int &left);
    friend limited_int& operator*= (limited_int &left, const limited_int &right);
    */
    friend bool operator== (const limited_int &right, const limited_int &left);

};