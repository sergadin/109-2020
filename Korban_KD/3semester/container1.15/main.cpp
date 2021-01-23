#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>


void trim(std::string &str);

class AVLcontainer 
{
private:
      class Node 
      {
      public:
          int val = 0;
          double dval = 0;
          int * intarr = nullptr;
          double *darr = nullptr;
          char *string = nullptr; 
          
          int len_int = 0;
          int len_double = 0;
          
          char *key = nullptr;
          
		// the height of this node from the deepest point
          int height;
          Node *left_child = nullptr;
          Node *parent = nullptr;
          Node *right_child = nullptr;
        
          
          Node();
          ~Node();
          Node(const Node & that);
          Node(const char *key ,const int val);
          Node(const char *key ,const double dval);
          Node(const char *key ,const char* string);
          Node(const char *key , const int* valarr, int n);
          Node(const char *key , const double* valarr, int n);
          
		// calculate the balance point.
          int getBalance();
          
          void removeParent();
          Node *setLeftChild(Node *newLeft);
          Node *setRightChild(Node *newRight);
          int updateHeight();
	};
    
    Node *root = nullptr;
    
private:
    void delete_all(Node * A);
    void deleteSubtree(Node *subtree, int depth, int level, bool first);
    
    void balanceAtNode(Node *n);
	Node *findNode(const char *key);
    
	void printSubtree(Node *subtree, int depth,
    int offset, bool first=1 );
    int spacing(int offset);
    
	void rotateLeft(Node *n);
	void rotateRight(Node *n);
    
	void setRoot(Node *n);

    void copytree(Node & A,const Node  & B);

public:
    AVLcontainer();
    ~AVLcontainer();
    AVLcontainer(const AVLcontainer & that);
    
    AVLcontainer operator = (const AVLcontainer & that);
    
    int getInt(const char* key) ;
    double getDouble(const char* key);
    char *getString(const char* key);
    int *getIntArray(const char* key);
    double *getDoubleArray(const char* key) ;
    
    
    int getHeight();
    
    bool insert( const char *key, const int val);
    bool insert(const char *key,const double val);
    bool insert(const char *key,const char* string);
    bool insert(const char *key,const int* val, int n);
    bool insert(const char *key, const double* val, int n );
    
    bool remove(const char* key);
    
    void print();
    
    bool readFile(std::ifstream & infile);
    
    
    enum ERRORS
    {
        NO_KEY = -10,
        NO_STRING,
        NO_INT_ARR,
        NO_DOUBLE_ARR,
        W_FORMAT,
    };
    
   
}; 

class AvlTree_exeption
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		AvlTree_exeption(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};



AVLcontainer::Node::Node(const char *key ,const int val) 
{
    this->key =  new char[strlen(key) + 1];
    strcpy(this->key, key);
    this->val = val;
    height = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AVLcontainer::Node::Node(const char *key ,const double dval) 
{
    this->key =  new char[strlen(key) + 1];
    strcpy(this->key, key);
    this->dval = dval;
    height = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AVLcontainer::Node::Node(const char *key , const char* string) 
{
    this->key =  new char[strlen(key) + 1];
    strcpy(this->key, key);
    
    this->string =  new char[strlen(string) + 1];
    strcpy(this->string, string);
    
    height = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AVLcontainer::Node::Node(const char *key , const int* valarr, int n) 
{
    this->key =  new char[strlen(key) + 1];
    strcpy(this->key, key);
    
    this->intarr =  new int[n];
    for (int i = 0; i < n; i++)
    {
        this->intarr[i] = valarr[i];
    }
    this->len_int = n;
    height = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AVLcontainer::Node::Node(const char *key , const double* valarr, int n) 
{
    this->key =  new char[strlen(key) + 1];
    strcpy(this->key, key);
    
    this->darr =  new double[n];
    for (int i = 0; i < n; i++)
    {
        this->darr[i] = valarr[i];
    }
    this->len_double = n;
    height = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AVLcontainer::Node::~Node()
{
    delete[] key;
    delete[] intarr;
    delete[] darr;
    delete[] string;
}

AVLcontainer::Node::Node(const Node & that)
{
    this->val = that.val;
    this->dval = that.dval;
    
    if(that.intarr != nullptr)
    {
        this->intarr =  new int[that.len_int];
        for (int i = 0; i < that.len_int; i++)
        {
            this->intarr[i] = that.intarr[i];
        }
        this->len_int = that.len_int;
    }
    
    if(that.intarr != nullptr)
    {
        this->darr =  new double[that.len_double];
        for (int i = 0; i < that.len_double; i++)
        {
            this->darr[i] = that.darr[i];
        }
        this->len_double = that.len_double;
    }
    
    if(that.string != nullptr)
    {
        this->string =  new char[strlen(that.string) + 1];
        strcpy(this->string, that.string);
    }
    
    this->key =  new char[strlen(that.key) + 1];
    strcpy(this->key, that.key);
    
    this->height = that.height;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
    
}

// returns balance 
//negative if right side is deeper 
//0 if deapth are the same 
//positive f left side is deeper 
int AVLcontainer::Node::getBalance() 
{

    int result;
    if (left_child == nullptr)
        if (right_child == nullptr)
            result = 0;
        else
            result = -right_child->height-1;
        
        else if (right_child == nullptr)
            result = left_child->height+1;
        
        else
            result = left_child->height-right_child->height;
        return result;
} 



void AVLcontainer::Node::removeParent() 
{
    parent = nullptr;
} 


AVLcontainer::Node *AVLcontainer::Node::setLeftChild(Node *newLeft) 
{
    if (newLeft != nullptr)
        newLeft->parent = this;
    left_child = newLeft;
    updateHeight();
    return left_child;
} 


AVLcontainer::Node *AVLcontainer::Node::setRightChild(Node *newRight) 
{

    if (newRight != nullptr)
        newRight->parent = this;
    right_child = newRight;
    updateHeight();
    return right_child;
} 

int AVLcontainer::Node::updateHeight() 
{

    if (left_child == nullptr)

        if (right_child == nullptr)
            height = 0;
        
        else
            height = right_child->height+1;
        
        else if (right_child == nullptr)
            height = left_child->height+1;
        
        else if (left_child->height > right_child->height)
            height = left_child->height+1;
        
        else
            height = right_child->height+1;
        return height;
} 


AVLcontainer::AVLcontainer() 
{
    root = nullptr;
}

AVLcontainer::~AVLcontainer()
{
    printf("destructor for AVLtree was Called\n");
    //delete_all(root);
    
    while (root!=nullptr) 
        remove(root->key);
        
}

void AVLcontainer::delete_all(Node * n) 
{
    if(n)
    {
        delete_all(n->left_child);
        delete_all(n->right_child);
        delete n;
    }
}

AVLcontainer::AVLcontainer(const  AVLcontainer & that)
{
    this->root = new Node(*that.root);
    this->root->parent  = nullptr;
    
    copytree(*this->root, *that.root);
}

AVLcontainer AVLcontainer::operator = (const AVLcontainer & that)
{
    
    if(that.root == this->root)
        return that;
    
    delete_all(this->root);
    
    this->root = new Node(*that.root);
    this->root->parent  = nullptr;
    
    copytree(*this->root, *that.root);
    
    
    return *this;
}

void AVLcontainer::copytree(Node & A ,const Node & B)
{
    //if(&B !=nullptr)
    {
        if(B.left_child)
        {
            A.left_child = new Node(*B.left_child);
            A.left_child->parent = &A;
            
            //printf("left %s\n",A.left_child->key);
            copytree(*A.left_child, *B.left_child);
        }
        else
            A.left_child = nullptr;
        
        if(B.right_child)
        {
            A.right_child = new Node(*B.right_child);
            A.right_child->parent = &A;
            
           //printf("right %s\n",A.right_child->key);
            copytree(*A.right_child, *B.right_child);
        }
        else
            A.right_child = nullptr;
        
    }
}


int AVLcontainer::getInt(const char* key) 
{ 
    Node *temp = findNode(key);
    if(!temp)
    {
        throw AvlTree_exeption(NO_KEY, "this key doesn't exist");
    }
    return temp->val; 
}
double AVLcontainer::getDouble(const char* key)
{ 
    Node *temp = findNode(key);
    if(!temp)
    {
        throw AvlTree_exeption(NO_KEY, "this key doesn't exist");
    }
        
    return temp->dval;
}

char * AVLcontainer::getString(const char* key) 
{ 
    Node *temp = findNode(key);
        
    if(!temp)
    {
        throw AvlTree_exeption(NO_KEY, "this key doesn't exist");
    }
        
    if(temp->string == nullptr)
    {
        throw AvlTree_exeption(NO_STRING, "in this key string is empty");
    }
        
    char *copy = new char[strlen(temp->string) + 1];
    strcpy(copy, temp->string);
    return copy; 
}

int *AVLcontainer::getIntArray(const char* key) 
{
    Node *temp = findNode(key);
    if(!temp)
    {
        throw AvlTree_exeption(NO_KEY, "this key doesn't exist");
    }
    
    if(temp->intarr == nullptr)
    {
        throw AvlTree_exeption(NO_INT_ARR, "in this key int array is empty");
    }
    int *copy = new int[temp->len_int];
    for (int i = 0; i < temp->len_int; i++)
        copy[i] = temp->intarr[i];
    return copy; 
}

double *AVLcontainer::getDoubleArray(const char* key) 
{
    Node *temp = findNode(key);
    if(!temp)
    {
        throw AvlTree_exeption(NO_KEY, "this key doesn't exist");
    }
    
    if(temp->darr == nullptr)
    {
        throw AvlTree_exeption(NO_DOUBLE_ARR, "in this key double array is empty");
    }
    double *copy = new double[temp->len_double];
    for (int i = 0; i < temp->len_double; i++)
        copy[i] = temp->darr[i];
    return copy; 
}


// balance the subtree
void AVLcontainer::balanceAtNode(Node *n) 
{

    //get current balance, if its bad on left side 
    //rotate it right adjusting the subtree left, if required
    int bal = n->getBalance();
    if (bal > 1) 
    {
        if (n->left_child->getBalance() < 0)
            rotateLeft(n->left_child);
        rotateRight(n);

    //otherwise its bad on right side 
    //rotate it left adjusting the subtree right, if required
    }
    else if (bal < -1) 
    {
        if (n->right_child->getBalance() > 0)
            rotateRight(n->right_child);
        rotateLeft(n);
    }
}

// Find the node containing the data.
AVLcontainer::Node *AVLcontainer::findNode(const char* key) 
{

    Node *temp = root;
    while (temp != nullptr) 
    {
        if (strcmp(temp->key, key) == 0)
            break;
        else if (strcmp(temp->key, key) < 0)
            temp = temp->left_child;
        else
            temp = temp->right_child;
    } 
    return temp;
} 

int AVLcontainer::getHeight()
{
    return root->height;
} 

bool AVLcontainer::insert(const char *key,int val) 
{
    
    //check if tree is empty
    if (root == nullptr)
        root = new Node(key, val);

    //  finding the insertion point 
    else 
    {
        Node *added_node = nullptr;
        Node *temp = root;
        while (temp != nullptr && added_node == nullptr) 
        {

            if ( strcmp(temp->key, key) < 0 ) 
            {
                if (temp->left_child == nullptr) 
                {
                    added_node = temp->setLeftChild(
                        new Node(key, val));
                } else
                    temp = temp->left_child;

            } 
            else if ( strcmp(key, temp->key) < 0 ) 
            {
                if (temp->right_child == nullptr)
                {
                    added_node = temp->setRightChild(new Node(key, val));
                } 
                else
                    temp = temp->right_child;

            
            } 
            //key is already in the tree
            else
            {
                if(temp->val == val)
                    return false;
                
                temp->val = val;
                return true;
            }
        } 
	//from the new node update height
	temp = added_node;
    while(temp != nullptr) 
    {
        temp->updateHeight();
        balanceAtNode(temp);
        temp = temp->parent;
	}
  } 
  return true;
}

bool AVLcontainer::insert(const char *key,double val) 
{

    //check if tree is empty
    if (root == nullptr)
        root = new Node(key, val);

    //  finding the insertion point 
    else 
    {
        Node *added_node = nullptr;
        Node *temp = root;
        while (temp != nullptr && added_node == nullptr) 
        {
            if ( strcmp(temp->key, key) < 0 ) 
            {
                if (temp->left_child == nullptr) 
                {
                    added_node = temp->setLeftChild(
                        new Node(key, val));
                } else
                    temp = temp->left_child;
            } 
            else if ( strcmp(key, temp->key) < 0 ) 
            {
                if (temp->right_child == nullptr)
                {
                    added_node = temp->setRightChild(new Node(key, val));
                } 
                else
                    temp = temp->right_child;
            
            } 
            //key is already in the tree
            else
            {
                if(abs(temp->dval - val) < 1e-10)
                    return false;
                
                temp->dval = val;
                return true;
            }
        } 

	//from the new node update height
	temp = added_node;
    while(temp != nullptr) 
    {
        temp->updateHeight();
        balanceAtNode(temp);
        temp = temp->parent;
	} 
  } 
  return true;
}

bool AVLcontainer::insert(const char *key,const char* val) 
{

    //check if tree is empty
    if (root == nullptr)
        root = new Node(key, val);

    //  finding the insertion point 
    else 
    {
        Node *added_node = nullptr;
        Node *temp = root;
        while (temp != nullptr && added_node == nullptr) 
        {
            if ( strcmp(temp->key, key) < 0 ) 
            {
                if (temp->left_child == nullptr) 
                {
                    added_node = temp->setLeftChild(
                        new Node(key, val));
                } else
                    temp = temp->left_child;
            } 
            else if ( strcmp(key, temp->key) < 0 ) 
            {
                if (temp->right_child == nullptr)
                {
                    added_node = temp->setRightChild(new Node(key, val));
                } 
                else
                    temp = temp->right_child;
                
            
            } 
            //key is already in the tree
            else
            {
                if(temp->string == nullptr)
                {
                    temp->string =  new char[strlen(val) + 1];
                    strcpy(temp->string, val);
                    return true;
                }
                if(strcmp(val, temp->string) == 0)
                    return false;
                
                delete temp->string;
                temp->string =  new char[strlen(val) + 1];
                strcpy(temp->string, val);
                return true;
            }
        } 

	//from the new node update height
	temp = added_node;
    while(temp != nullptr) 
    {
        temp->updateHeight();
        balanceAtNode(temp);
        temp = temp->parent;
	} 
  } 
  return true;
}

bool AVLcontainer::insert(const char *key, const int* val, int n ) 
{
    //check if tree is empty
    if (root == nullptr)
        root = new Node(key, val, n);

    //  finding the insertion point 
    else 
    {
        Node *added_node = nullptr;
        Node *temp = root;
        while (temp != nullptr && added_node == nullptr) 
        {
            if ( strcmp(temp->key, key) < 0 ) 
            {
                if (temp->left_child == nullptr) 
                {
                    added_node = temp->setLeftChild(
                        new Node(key, val, n));
                } else
                    temp = temp->left_child;
            } 
            else if ( strcmp(key, temp->key) < 0 ) 
            {
                if (temp->right_child == nullptr)
                {
                    added_node = temp->setRightChild(new Node(key, val, n));
                } 
                else
                    temp = temp->right_child;

            } 
            //key is already in the tree
            else
            {
                if(temp->intarr == nullptr)
                {
                    temp->intarr = new int[n];
                    for (int i = 0; i < n; i++)
                        temp->intarr[i] = val[i];
                    
                    temp->len_int = n;
                    
                    return true;
                }
                delete[] temp->intarr;
                temp->intarr = new int[n];
                for (int i = 0; i < n; i++)
                    temp->intarr[i] = val[i];
                
                temp->len_int = n;
                
                return true;
            }
        } 

	//from the new node update height
	temp = added_node;
    while(temp != nullptr) 
    {
        temp->updateHeight();
        balanceAtNode(temp);
        temp = temp->parent;
	} 
  } 
  return true;
}

bool AVLcontainer::insert(const char *key, const double* val, int n ) 
{
    //check if tree is empty
    if (root == nullptr)
        root = new Node(key, val, n);

    //  finding the insertion point 
    else 
    {
        Node *added_node = nullptr;
        Node *temp = root;
        while (temp != nullptr && added_node == nullptr) 
        {
            if ( strcmp(temp->key, key) < 0 ) 
            {
                if (temp->left_child == nullptr) 
                {
                    added_node = temp->setLeftChild(
                        new Node(key, val, n));
                } else
                    temp = temp->left_child;
            } 
            else if ( strcmp(key, temp->key) < 0 ) 
            {
                if (temp->right_child == nullptr)
                {
                    added_node = temp->setRightChild(new Node(key, val, n));
                } 
                else
                    temp = temp->right_child;

            } 
            //key is already in the tree
            else
            {
                if(temp->darr == nullptr)
                {
                    temp->darr = new double[n];
                    for (int i = 0; i < n; i++)
                        temp->darr[i] = val[i];
                    
                    temp->len_double = n;
                    
                    return true;
                }
                delete[] temp->darr;
                temp->darr = new double[n];
                for (int i = 0; i < n; i++)
                    temp->darr[i] = val[i];
                
                temp->len_double = n;
                
                return true;
            }
        } 

	//from the new node update height
	temp = added_node;
    while(temp != nullptr) 
    {
        temp->updateHeight();
        balanceAtNode(temp);
        temp = temp->parent;
	} 
  } 
  return true;
}



void AVLcontainer::print() 
{

    if (root == nullptr)
	std::cout << "Tree is empty!" <<
		std::endl;
        else if (root->height > 4)
            std::cout << "Not currently supported!" <<
		std::endl;
        else 
        {
            int max = root->height;
            for (int depth = 0; depth <= max; depth++) 
            {
                printSubtree(root, depth, max-depth+1, true);
                std::cout << std::endl;
            } 
            
        } 
} 

// leftmost branch will have first true  
// the level counts up from the bottom
// for the line we are doing. the depth is how
// many layers to skip over
void AVLcontainer::printSubtree(Node *subtree, int depth,
	int level, bool first) 
{
    if (depth > 0) 
    {
        if (subtree == nullptr) 
        {
            printSubtree(subtree, depth-1, level, first);
            printSubtree(subtree, depth-1, level, false);
        } 
        else 
        {
            printSubtree(subtree->left_child, depth-1,level, first);
            printSubtree(subtree->right_child, depth-1,level, false);
        } 
    } 
    else 
        if (subtree == nullptr)
            std::cout << std::setw((first)?
            spacing(level)/2:spacing(level)) << "-";

        else
            std::cout << std::setw((first)?
            spacing(level)/2:spacing(level)) <<
            subtree->key << '(' << subtree->val << ')';
} 

// remove the value from the tree.
// Returns:
//		 true: if removal is successful
//		 false: if item is not found in the tree
//
bool AVLcontainer::remove(const char* key) 
{

    Node *toBeRemoved = findNode(key);
    if (toBeRemoved == nullptr)
        return false;

    enum {left, right} side;
    Node *p = toBeRemoved->parent;
    if (p != nullptr &&
        p->left_child == toBeRemoved)
        side = left;
    else
        side = right;
    if (toBeRemoved->left_child == nullptr)
        if (toBeRemoved->right_child == nullptr) 
        {
            if (p == nullptr) 
            {
                setRoot(nullptr);
                delete toBeRemoved;
            } 
            else 
            {
                if (side == left)
                    p->setLeftChild(nullptr);
                else
                    p->setRightChild(nullptr);
                delete toBeRemoved;
                p->updateHeight();
                balanceAtNode(p);
                
            } 

        }
        else 
        {

            if (p == nullptr) 
            {
                setRoot(toBeRemoved->right_child);
                delete toBeRemoved;
            } 
            else 
            {
                if (side == left)
                    p->setLeftChild(toBeRemoved->
                    right_child);
                else
                    p->setRightChild(toBeRemoved->
                    right_child);
                delete toBeRemoved;
                p->updateHeight();
                balanceAtNode(p);
                
            } 
        }
        else if (toBeRemoved->right_child ==nullptr) 
        {

            if (p == nullptr) 
            {
                setRoot(toBeRemoved->left_child);
                delete toBeRemoved;
            } 
            else
            {
                if(side == left)
                    p->setLeftChild(toBeRemoved->left_child);
                else
                    p->setRightChild(toBeRemoved->left_child);
                delete toBeRemoved;
                p->updateHeight();
                balanceAtNode(p);
                
            }
        } 
        else 
        {
            Node *replacement;
            Node *replacement_parent;
            Node *temp_node;
            int bal = toBeRemoved->getBalance();
            if (bal > 0) 
            {
                if (toBeRemoved->left_child->right_child == nullptr) 
                {
                    replacement = toBeRemoved->left_child;
                    replacement->setRightChild(
                        toBeRemoved->right_child);
                    temp_node = replacement;
                } 
                else 
                {
                    replacement = toBeRemoved->left_child->right_child;
                    while (replacement->right_child !=nullptr)
                        replacement = replacement->right_child;
                    replacement_parent = replacement->parent;
                    replacement_parent->setRightChild(replacement->left_child);
                    temp_node = replacement_parent;
                    replacement->setLeftChild(toBeRemoved->left_child);
                    replacement->setRightChild(toBeRemoved->right_child);
                    
                }


                
            } 
            else 
                if (toBeRemoved->right_child->left_child == nullptr) 
                {
                    replacement = toBeRemoved->right_child;
                    replacement->setLeftChild(
                        toBeRemoved->left_child);
                    temp_node = replacement;
                } 
                else 
                {
                    replacement = toBeRemoved->
                    right_child->left_child;
                    while (replacement->left_child !=nullptr)
                        replacement = replacement->left_child;
                    replacement_parent = replacement->parent;
                    replacement_parent->setLeftChild(replacement->right_child);
                    temp_node = replacement_parent;
                    replacement->setLeftChild(
                        toBeRemoved->left_child);
                    replacement->setRightChild(
                        toBeRemoved->right_child);
                    
                }
            if (p == nullptr)
                setRoot(replacement);
            else if (side == left)
                p->setLeftChild(replacement);
            else
                p->setRightChild(replacement);
            delete toBeRemoved;
            balanceAtNode(temp_node);
        }
        return true;
} 

void AVLcontainer::rotateLeft(Node *n) 
{

    enum {left, right} side;
    Node *p = n->parent;
    if (p != nullptr && p->left_child == n)
        side = left;
    else
        side = right;
    
    Node *temp = n->right_child;
    n->setRightChild(temp->left_child);
    temp->setLeftChild(n);

    if (p == nullptr)
        setRoot(temp);
    else if (side == left)
        p->setLeftChild(temp);
    else
        p->setRightChild(temp);
} 

void AVLcontainer::rotateRight(Node *n) 
{
    enum {left, right} side;
    Node *p = n->parent;
    if (p != nullptr && p->left_child == n)
        side = left;
    else
        side = right;

    Node *temp = n->left_child;
    n->setLeftChild(temp->right_child);
    temp->setRightChild(n);

    if (p == nullptr)
        setRoot(temp);
    else if (side == left)
        p->setLeftChild(temp);
    else
        p->setRightChild(temp);
}


void AVLcontainer::setRoot(Node *n) 
{
  root = n;
  if (root != nullptr)
	root->removeParent();
} 

// default spacing for element. Each
// higher level doubles the preceeding
int AVLcontainer::spacing(int level) 
{
  int result = 6;
  for (int i = 0; i < level; i++)
	result += result;
  return result;
} 

void trim(std::string &str)
{
    int i=0;

    //left trim
    while (isspace(str[i])!=0)
        i++;
    str = str.substr(i,str.length()-i);

    //right trim
    i=str.length()-1;
    while (isspace(str[i])!=0)
        i--;
    str = str.substr(0,i+1);
}


bool AVLcontainer::readFile(std::ifstream  & infile)
{
    std::string line;
    while(getline(infile, line)) 
    {
        std::string key(line, 0, line.find('='));
        std::string value(line,line.find('=') + 1);
        
        trim(key);
        trim(value);
        
        std::string type(value, 0, value.find(' '));
        //std::cout << type << std::endl;
        if (type == "int")  
        {
            value = value.substr(value.find(' ') );
            trim(value);
            insert( key.c_str(), std::stoi(value));
        }
        else if(type == "int")
        {
            value = value.substr(value.find(' ') );
            trim(value);
            insert( key.c_str(), std::stod(value));
        }
        else if(type == "char*")
        {
            value = value.substr(value.find(' ') );
            trim(value);
            insert( key.c_str(), value.c_str());
        }
        else if(type.substr(0, value.find('[')) == "int")
        {
            
            int n = std::stoi(type.substr(value.find('[') + 1));
            
            int *arr = new int[n];

            for( int i = 0; i < n; i++)
            {
                
                value = value.substr(value.find(' ') );
                trim(value);
                arr[i] = std::stoi(value);
            }
            insert( key.c_str(), arr, n);
            delete[] arr;
        }
        else if(type.substr(0, value.find('[')) == "double")
        {
            
            int n = std::stoi(type.substr(value.find('[') + 1));
            
            double *arr = new double[n];

            for( int i = 0; i < n; i++)
            {
                
                value = value.substr(value.find(' ') );
                trim(value);
                arr[i] = std::stod(value);
            }
            insert( key.c_str(), arr, n);
            delete[] arr;
        }
        else
        {
            throw AvlTree_exeption(W_FORMAT, "wrong format");
        }
        
                
    }
    return true;
}


int main() 
{
    try
    {
        double data[20];
        int data2[20];
        srand(time(0));
        AVLcontainer tree;
        
        std::ifstream myfile;
        myfile.open("test.txt");
        
        if(!myfile.is_open()) 
        {
            std::cout << "File error"<< std::endl;
            return 1;
        }
        
        char * test;
        tree.readFile(myfile);
        test = tree.getString("a");
        std::cout << test << std::endl;
        delete[] test;
        
        int * int_arr;
        int_arr = tree.getIntArray("a");
        std::cout << int_arr[0] << std::endl;
        delete[] int_arr;
        
        double *double_arr;
        double_arr = tree.getDoubleArray("a");
        std::cout << double_arr[0] << std::endl;
        delete[] double_arr;
        
        
        const char *basekey = "112112";
        
        int nuber_of_iter = 5;
        
        for (int i = 0; i < nuber_of_iter; i++) 
        {
            //char * str;
            data[i] = rand()%100;
            //sprintf(str, "%d");
            if(!tree.insert(basekey + i,data[i]))
                break;
            std::cout << "Adding " << i << " " <<data[i] << 
            " ##############################################################" << std::endl;
            //tree.print();
        }
        
        for (int i = 0; i < nuber_of_iter; i++) 
        {
            //char * str;
            data2[i] = rand()%100;
            //sprintf(str, "%d");
            if(!tree.insert(basekey + i,data2[i]))
                break;
            std::cout << "Adding " << i << " " <<data2[i] << 
            " ##############################################################" << std::endl;
            //tree.print();
            
        }
        for (int i = 0; i < nuber_of_iter; i++) 
        {
            if(!tree.insert(basekey + i,basekey + i))
                break;
            //std::cout << "Adding " << i << " " <<data2[i] << 
            //" ##############################################################" << std::endl;
            //tree.print();
        }

        {
            printf("1######################################\n");
            char *str;
            int *temp;
            double *temp2;
            AVLcontainer A;
            A = tree;
            
            printf("%d^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", A.getInt(basekey));
            printf("%lf^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", A.getDouble(basekey));
            
            printf("%s^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", 
            str = A.getString(basekey));
            
            A.insert(basekey, data2, nuber_of_iter);
            temp = A.getIntArray(basekey);
            
            printf("%d^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", temp[1]);
            
            A.insert(basekey, data, nuber_of_iter);
            temp2 = A.getDoubleArray(basekey);
            printf("%lf^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n", temp2[1]);
            
            delete[] temp2;
            delete[] temp;
            delete[] str;
            tree = A;
            printf("2######################################\n");
        }
        
        for (int i = 0; i < nuber_of_iter; i++) {
            std::cout << "Removing " << basekey + i << std::endl;
            std::cout << tree.remove(basekey + i) << 
            " ##############################################################" << std::endl;
            //tree.print();
            
        }
    }
    catch (AvlTree_exeption &err)
    {
		std::cout << "EXC  "<< err.get_reason() << std::endl;
    }
    return 0;
} 
