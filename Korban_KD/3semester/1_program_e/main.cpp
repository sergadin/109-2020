#include <iostream>
#include "list_arr.h" 

using namespace std;

int main(void) 
{
    try
    {
        
        list_arr<int> A ;
        int *c;
        list_arr<int> b = A;
        
        for(int i  = 0; i < 10; i++)
        {
            A[i]  = i;
        }
        b = A;
        b[2] = 15651;
        
        cout << "oparator= cheak: " << b[2] <<endl;
        c = b.front();
        cout << "func front cheak: " << c[6] <<endl;
        delete[] c;
        b = A;
        c = b.back();
        cout << "func back cheak: " << c[9] <<endl;
        b.pop_front();
        cout << "func pop_front cheak: " << b.empty() << endl;
        cout << "func size() cheak: b.size(): " << b.size() << endl;
        b = A;
        b.pop_back();
        cout << "func pop_back cheak: " << b.empty() << endl;
        cout << "func size() cheak: b.size(): " << b.size() << endl;
        b.expand(40);
        b[29] = 1265;
        cout << "func expand cheak: b.size(): " << b.size() << " b[29]:" << b[29] << endl;
        b.shrink(39);
        cout << "func shrink cheak: b.size(): " << b.size() << " " << b.empty() << endl;
        delete[] c;
        
        
    }
    catch (list_arr_exception &err)
    {
		std::cout << "EXC  "<< err.get_reason() << std::endl;
    }
    return 0;
}

