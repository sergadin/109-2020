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
    Iterator<int> last(a.end());
    for(Iterator<int> it(a.begin()); it != last; ++it) {
        cout<< *it;
    }
    return 0;
}
