#ifndef EXAM_TEST 
#define EXAM_TEST

#include <stdio.h>
#include <new>

// graph node structure
struct Node
{
    int id;       // id of this vertex
    int length; //length of branch
    Node *left, *right;  // pointers to siblings
    int parents; //number of parents
  
	// simplest constuctor
    Node()
    {
        left = right = nullptr;
        parents = 0;
        length = -1;
    }
};

// search for node with given id
Node* GetNode(Node *p, int id);

// read graph from file,
// maxId will be the maximal id among all graph nodes
Node* ReadGraph(char *fname, int &maxId);

// delete the graph  (like destructor)
void DeleteGraph(Node *root, int maxId);

// print the graph  
void PrintGraph(FILE *f, Node *root);


void Tree(Node *root, int maxId);
Node* findParent(Node *special, Node *root, int maxId);
void deleteParents(Node *special, Node* root, Node *parent, int maxId);

#endif // EXAM_TEST








