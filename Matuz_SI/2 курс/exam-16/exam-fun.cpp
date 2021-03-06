#include "exam-test.h"

Node* GetNode (Node *p, int id)
{
    Node *q;
    if (!p)
        return nullptr;
    if (p->id == id)
        return p;
    q = GetNode(p->left, id);

    return (q)? q : GetNode(p->right, id);
}

Node* ReadGraph(char *fname, int &maxId)
{
    // file format (list of edges, left or right):
    // parent_id   L/R   child_id

    // the function does not check id of vertices for coincidence,
    // i.e., the file should be correct
    // parent nodes should precede their siblings

    for (char *s = fname; *s; ++s)
        if (*s=='\n' || *s=='\r')
            *s = 0;

    FILE *f = fopen(fname,"r");
    if (!f)
    {
        fprintf(stderr, "cannot open %s\n", fname);
        return nullptr;
    }

    Node *root = nullptr;
    Node *p, *q;
    int id, parid;
    char dir[8];
    maxId = -1;
    while (fscanf(f, "%d%s%d", &parid, dir, &id) == 3) 
    {
        printf("%d %s %d\n", parid, dir, id);
        if (!root)
        {
            root = new Node;
            root->id = parid;
            root->parents = 0;
            root->length = 1;
        }

        p = GetNode(root, parid);
        if (!p)
            break;
        if (dir[0] == 'L' && p->left)
            break;
        if (dir[0] == 'R' && p->right)
            break;

        q = GetNode(root, id);
        if (!q)
            q = new Node;
        q->id = id;
        ++(q->parents);
        if (q->length == -1)
            q->length= p->length + 1;
        else
            q->length = q->length < p->length + 1 ? q->length : p->length + 1;

        if (maxId < id) maxId = id;
        if (dir[0] == 'L') p->left = q;
        if (dir[0] == 'R') p->right = q;
    }

    fclose(f);
    return root;
}

void DeleteGraph(Node *root, int maxId)
{
    if (!root)
        return;
    Node **nodes = new Node*[maxId + 1];
    for (int i = 0; i<= maxId; i++)
        nodes[i] = GetNode(root, i);

    for (int i=0; i<=maxId; i++)
        if (nodes[i])
            delete nodes[i];

    delete[] nodes;
}

void PrintGraph(FILE *f, Node *root)
{
    if (!f)
        return;
    if (!root)
        return;

// fprintf(f, "node %3d parNum %3d  ", root->id, root->parents);
    fprintf(f, "node %3d ", root->id);
    if (root->left)
        fprintf(f, "L->%3d  ", root->left->id);
    if (root->right)
        fprintf(f, "R->%3d  ", root->right->id);
    fputc('\n',f);
    PrintGraph(f, root->left);
    PrintGraph(f, root->right);
}

void Tree(Node *root, int maxId)
{
    for (int i = 0; i <= maxId; ++i)
    {
        Node* curr = GetNode(root, i);
        if (curr && curr->parents > 1)
        {
            Node* parent = findParent(curr, root, maxId);
            deleteParents(curr, root, parent, maxId);
        }
    }
}

Node* findParent(Node* special, Node* root, int maxId)
{
    int min_length = maxId + 1;
    Node* parent = nullptr;

    for (int i = 0; i <= maxId; ++i)
    {
        Node* p = GetNode(root, i);
        if (p && (p->left == special || p->right == special) && (p->length < min_length))
        {
            min_length = p->length;
            parent = p;
        }
    }

    return parent;
}

void deleteParents(Node *special, Node *root, Node *parent, int maxId) {
    for (int i = 0; i <= maxId; ++i) 
    {
        Node* p = GetNode(root, i);
        if (p && p->left == special && p != parent)
        {
            p->left = nullptr;
            --(special->parents);
        }
        if (p && p->right == special && p != parent)
        {
            p->right = nullptr;
            --(special->parents);
        }
    }
    special->length = parent->length + 1;
}
