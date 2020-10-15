#include "class.h"


int main(){
    limited_int a(1, 3), b(1, 6);
    a.put_element(2);
    cout << a.how_many() << endl;
    a.put_element(2);
    cout << a.how_many() << endl;
    a.put_element(6);
    cout << a.how_many() << endl;
    a.delete_element(2);
    cout << a.how_many() << endl;
    return 0;
}
