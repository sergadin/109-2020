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

    // test print of the graph
    PrintGraph(stdout, root);

    // you may insert your solution here

    int inc = 10;

    Node * rootInc = CopyInc(root, inc, maxId);

    PrintGraph(stdout, rootInc);

    DeleteGraph(root, maxId);
    DeleteGraph(rootInc, maxId + inc);
    return 0;
}










