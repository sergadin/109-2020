#include <stdio.h>
#include "stack.h"
#include "graph.h"
#include <algorithm>
#include <vector>

using namespace std;


int Graph::LoadForTest1()
{
    nStartNodes = 5;
    start = new Node*[nStartNodes];
    Node * p9 = new Node(9, nullptr);
    Node * p8 = new Node(8, p9);
    Node * p7 = new Node(7, p8);
    Node * p6 = new Node(6, p7);
    start[0] = new Node(1, p6);
    start[1] = new Node(2, p6);
    start[2] = new Node(3, p7);
    start[3] = new Node(4, p8);
    start[4] = new Node(5, p9);
    return nStartNodes;
}

int Graph::LoadForTest2()
{
    nStartNodes = 5;
    start = new Node*[nStartNodes];
    Node * p14 = new Node(14, nullptr);
    Node * p13 = new Node(13, nullptr);
    Node * p12 = new Node(12, p14);
    Node * p11 = new Node(11, p13);
    Node * p6 = new Node(6, p11);
    Node * p7 = new Node(7, p11);
    Node * p8 = new Node(8, p11);
    Node * p9 = new Node(9, p12);
    Node * p10 = new Node(10, p12);
    start[0] = new Node(1, p6);
    start[1] = new Node(2, p7);
    start[2] = new Node(3, p8);
    start[3] = new Node(4, p9);
    start[4] = new Node(5, p10);
    return nStartNodes;
}

int Graph::LoadForTest3()
{
    nStartNodes = 2;
    start = new Node*[nStartNodes];
    Node * p6 = new Node(6, nullptr);
    Node * p5 = new Node(5, p6);
    Node * p7 = new Node(7, p6);
    Node * p4 = new Node(4, p5);
    Node * p3 = new Node(3, p4);
    Node * p2 = new Node(2, p3);
    p6->next = p3;
    start[0] = new Node(1, p2);
    start[1] = new Node(8, p7);
    return nStartNodes;
}

int Graph::LoadForTest4()
{
    nStartNodes = 3;
    start = new Node*[nStartNodes];
    Node * p3 = new Node(3, nullptr);
    Node * p2 = new Node(2, p3);
    Node * p6 = new Node(6, nullptr);
    Node * p8 = new Node(8, p6);
    Node * p7 = new Node(7, p8);
    p6->next = p7;
    start[0] = new Node(1, p2);
    start[1] = new Node(4, p2);
    start[2] = new Node(5, p6);
    return nStartNodes;
}

int Graph::LoadForTest5()
{
    nStartNodes = 5;
    start = new Node*[nStartNodes];
    Node * p8 = new Node(8, nullptr);
    Node * p9 = new Node(9, nullptr);
    Node * p5 = new Node(5, p8);
    Node * p6 = new Node(6, p9);
    Node * p7 = new Node(7, p9);
    start[0] = new Node(1, p5);
    start[1] = new Node(2, p5);
    start[2] = new Node(3, p6);
    start[3] = new Node(4, p7);
    start[4] = new Node(10, nullptr);
    return nStartNodes;
}




   // Attention! 
   // Print function does not work for graphs with loops !!!
   // It falls into infinite cycle. 
   // You sould correct it for using with such graphs !!!

void Graph::Print(FILE *f, const char *text)
{
    if (!f) return;
    if (text) fprintf(f, "%s", text);
    for (int i=0; i<nStartNodes; i++) {
        for (Node *p = start[i]; p; p = p->next) {
            fprintf(f, "  %d ->", p->id);
        }
        fprintf(f, "  null\n");
    }
}

Graph::~Graph()
{
    Node *p;
    Stack<Node*> s;
    for (int i=0; i<nStartNodes; i++) {
       for (p = start[i]; p; p = p->next) {
           if (s.Contains(p)) break;
           s.Push(p);
       }
    }
    while (s.Pop(p)) delete p;
    delete[] start;
}

void Graph::Find_parts(FILE *f)
{
	vector<int> ids;
	vector<int> ids_temp;
	for(int i = 0; i<nStartNodes; i++)
	{
		int check = 0;
		Node* temp = start[i] -> next;
		while (temp)
		{
			if(find(ids.begin(), ids.end(), temp -> id) != ids.end())
			{
				if(find(ids_temp.begin(), ids_temp.end(), temp -> id) == ids_temp.end())
				{
					check = 1;
				}
				break;
			}
			else
			{
				ids.push_back(temp -> id);
				ids_temp.push_back(temp -> id);
			}
			temp = temp -> next;
		}
		if(check == 0)
		{
			fprintf(f, "\n\n New part of graph has started, its start nodes \n %d", start[i] -> id);
		}
		else
		{
			fprintf(f, "%d", start[i] -> id);
		}
		ids_temp.clear();
	}
}
