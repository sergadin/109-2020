#ifndef EXAM_TEST
#define EXAM_TEST

#include <stdio.h>
#include <new>

// graph node structure
struct Node
{
    int id;       // id of this vertex
    Node *left, *right;  // pointers to siblings

	// simplest constuctor
    Node() { left = right = nullptr; }
};


// search for node with given id
Node * GetNode (Node * p, int id);

// count amount of "parents"
int CountParents(Node *root, int nodeId, int *nodes_parents);

// read graph from file,
// maxId will be the maximal id among all graph nodes
Node * ReadGraph(char * fname, int &maxId);


// delete the graph  (like destructor)
void  DeleteGraph(Node *root, int maxId);

// print the graph  (nodes and their left and right siblings)
void PrintGraph(FILE *f, Node* root);

#endif // EXAM_TEST
