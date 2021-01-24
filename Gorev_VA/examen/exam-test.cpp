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
    printf("\n-\n-\n-\n");
    Node *root1 = Copy(root, 1);
    PrintGraph(stdout, root1);
             
    DeleteGraph(root, maxId);
    return 0;
}










