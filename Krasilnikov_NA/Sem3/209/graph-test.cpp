
#include <stdio.h>
#include "graph.h"


int main()
{
    Graph g;
    g.LoadForTest1();
    //g.LoadForTest2();
    //g.LoadForTest3();  // contains cycle
    //g.LoadForTest4();  // contains cycle
    //g.LoadForTest5();

    g.Print(stdout, "initial graph\n");

    // solve you problem here


    return 0;
}