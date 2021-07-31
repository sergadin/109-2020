#include "exam-test.h"

int main()
{
    Node *root;
    int maxId; 
    char fname[64];
    printf("data file name: ");
    char *s = fgets(fname, 64, stdin);
    root = ReadGraph(fname, maxId);
    if (!root || !s)
    {
       printf("cannot process file %s\n", fname);
       return -1;
    }

    // test print of the graph
    printf("old graph\n");
    PrintGraph(stdout, root);

    Tree(root, maxId);

    printf("new graph\n");
    PrintGraph(stdout, root);
             
    DeleteGraph(root, maxId);
    return 0;
}










