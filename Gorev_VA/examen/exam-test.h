#ifndef EXAM_TEST 
#define EXAM_TEST

#include <stdio.h>
#include <new>


// graph node structure
struct Node
{
    int id;       // id of this vertex
    Node *left, *right;  // pointers to siblings
    Node *help = nullptr;
    int max = -1;
    int ind = 0;
	// simplest constuctor
    Node() { left = right = Root = nullptr; }
};


// search for node with given id
Node * GetNode (Node * p, int id);


// read graph from file,
// maxId will be the maximal id among all graph nodes
Node * ReadGraph(char * fname, int &maxId);


// delete the graph  (like destructor)
void  DeleteGraph(Node *root, int maxId);


// print the graph  (nodes and their left and right siblings)
void PrintGraph(FILE *f, Node* root);


Node *Copy(Node *root, int incr);

#endif // EXAM_TEST








