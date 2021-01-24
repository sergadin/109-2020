#include "exam-test.h"


using namespace std;

Node * GetNode (Node * p, int id)
{
   Node *q;
   if (!p) return nullptr;
   if (p->id == id) return p;
   q = GetNode(p->left, id); 
   return (q)? q : GetNode(p->right, id); 
}

Node * ReadGraph(char * fname, int &maxId)
{
    // file format (list of edges, left or right):
    //  parent_id   L/R   child_id   

    // the function does not check id of vertices for coincidence, 
    // i.e., the file should be correct
    // parent nodes should precede their siblings

    for (char *s = fname; *s; ++s) if (*s=='\n' || *s=='\r') *s = 0;
    FILE *f = fopen(fname,"r");
    if (!f) {
        fprintf(stderr, "cannot open %s\n",fname);
        return nullptr;
    } 
    Node *root = nullptr;
    Node *p, *q;
    int id, parid;
    char dir[8];
    maxId = -1;
    while (fscanf(f, "%d%s%d", &parid, dir, &id) == 3) {
       printf("%d %s %d\n", parid, dir, id); 
       if (!root) {
          root = new Node;
          root->id = parid;
       }
       p = GetNode(root, parid);
       if (!p) break;
       if (dir[0] == 'L' && p->left) break;
       if (dir[0] == 'R' && p->right) break;
       q = GetNode(root, id);
       if (!q) q = new Node;
       q->id = id;
       if (maxId < id) maxId = id;
       if (dir[0] == 'L') p->left = q;
       if (dir[0] == 'R') p->right = q;
    }
    fclose(f);
    return root;
}

void  DeleteGraph(Node *root, int maxId)
{
   if (!root) return;
   Node **nodes = new Node*[maxId + 1];
   for (int i=0; i<=maxId; i++) {
      nodes[i] = GetNode(root, i);
   } 
   for (int i=0; i<=maxId; i++) {
      if (nodes[i]) delete nodes[i];
   } 
   delete [] nodes;
}

void PrintGraph(FILE *f, Node* root)
{
   if (!f) return;
   if (!root) return;
   fprintf(f, "node %3d  ", root->id); 
   if (root->left) fprintf(f, "L->%3d  ", root->left->id);  
   if (root->right) fprintf(f, "R->%3d  ", root->right->id);  
   fputc('\n',f);
   PrintGraph(f, root->left);
   PrintGraph(f, root->right);
}



void goq (Node *root, int x)
{
    if (root == 0) return;
    for(int i=0;i<1000;i++){
        if(root->A[i]==0){
            root->A[i]=x;
            break;
        }
    }
    goq(root->left, root->id);
    goq(root->right, root->id);
}

void gow (Node *root)
{ 
    if (root == 0) return;
    int i,j;
    for(i=0;i<1000;i++){
        for(j=i+1;j<1000;j++){
            if(root->A[i]==root->A[j]){
                root->A[j]=0;
            }
        }
    }
    for(i=0;i<1000;i++){
        for(j=i+1;j<1000;j++){
            if((root->A[i]==0)&&(root->A[j]!=0)){
                root->A[i]=root->A[j];
                root->A[j]=0;
            }
        }
    }
    gow(root->left);
    gow(root->right);
}

void goe (Node *root1, Node *root)
{ 
    if (root1 == 0) return;
    int i,n=0,r,j;
    int a[1000];
    Node *q;
    for(i=0;i<1000;i++){
        a[i]=0;
    }
    for(i=0;i<1000;i++){
        if(root1->A[i]!=0){
            n++;
        } else {
            break;
        }
    }
    if(n>1){
        for(i=0;i<n;i++){
            r=root1->A[i];
            if(r==0){break;}
            a[0]=root1->id;
            for(j=1;j<1000;j++){
                q=GetNode(root, r);
                if(q==0){break;}
                a[j]=q->id;                
                r=q->A[0];
            }
            printf("walk- ");
            for(j=99;j>-1;j--){
                if(a[j]!=0){
                    printf("%d ", a[j]);
                }
            }
            for(j=0;j<1000;j++){
                a[j]=0;
            }
            printf("\n");
        }
    }    
    goe(root1->left, root);
    goe(root1->right, root);
}
