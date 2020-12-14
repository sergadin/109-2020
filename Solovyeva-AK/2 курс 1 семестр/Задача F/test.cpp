#include "stack.h"
int main(){
    stack<int> a(2);
    a.push(9);
    a.print();
    cout << a.pop() << endl;
    a.print();
    
    stack<int> b = a;
    a = a + b;
    a.print();
    for(int i = 0; i < 5; i++){
        a.push(i);
    }
    stack<int>::Iterator last;
    stack<int>::Iterator it;
    last = a.end();
    for(it = a.begin(); it != last; ++it) {
        cout<< *it;
    }
    return 0;
}
