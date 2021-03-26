#include <vector>
#include "list.h"

template<class T>
ostream &operator<<(ostream& os, vector<T> &V)
{
    for (T i:V) cout << i << " ";
    cout << "\n";
    return os;
}

int main()
{
    vector<int> V;
    DeqList<vector<int>> a;
   
    Iterator<vector<int>> i = a.Head();
    for (int k = 0; k < 10; ++k)
    {
        V.push_back(k);
        a.InsAfter(i, V);
    }
    cout << a;
    ++i;
    for (; i != a.Head(); ++i) 
    {
        for (int j = 0; j < int((*i).size()); ++j)
            (*i)[j] *= 10;
    }
    cout << a;

    i = a.Head();
    a.DelForAfter(i);
    cout << a;

    DeqList<DeqList<vector<int>>> D;
    DeqList<DeqList<vector<int>>> E;
    Iterator<DeqList<vector<int>>> j;
    j = D.Head();
    cout << a;
    D.InsAfter(j, a);

    vector<int> W;


    W.push_back(500);
    a.InsBefore(i, W);
    D.InsBefore(j, a);


    W.push_back(1000);
    a.InsBefore(i, W);
    D.InsBefore(j, a);
    cout << D;
    D.DelForAfter(j);
 
    return 0;
}
