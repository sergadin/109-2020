#include "exam-test.h"


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
    int inc = 2;
    Node *newroot;
    newroot = CopyNodeWithIncrement(root, inc);

    // test print of the graph
    PrintGraph(stdout, newroot);

    // you may insert your solution here
             
    DeleteGraph(root, maxId);
    DeleteGraph(newroot, maxId+inc);
    return 0;
}










