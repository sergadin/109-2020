#include "exam-test.h"
#include <iostream>

using namespace std;
int main()
{
    Node *root;
    int maxId; 
    char fname[64];
    printf("data file name: ");
    char * s = fgets(fname, 64, stdin); 
    root = ReadGraph(fname, maxId);
    if (!root || !s) {
       printf("cannot process file %s\n", fname);
       return -1;
    }

    // test print of the graph
    PrintGraph(stdout, root);

    // you may insert your solution here
    
    goq (root, 0);
    gow (root);
    goe (root, root);
    
             
    DeleteGraph(root, maxId);
    return 0;
}










