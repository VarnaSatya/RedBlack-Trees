typedef struct node
{
    int val;
    struct node *l;
    struct node *r;
    struct node *p;
    int colour;    //red=0, black=1
}node;

typedef struct tree
{
    node *root;
    node* nil;
}tree;

void disp(tree T,node *root);
void insertion(tree *T,int val);
int verification(tree T);
int po(node *root,tree T,int *h);