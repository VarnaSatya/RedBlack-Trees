#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void disp(tree T,node *root)
{
    if(root==T.nil)
        return;
    
    disp(T,root->l);
    printf("%d %s\n",root->val,root->colour==0?"red":"black");
    disp(T,root->r);
}

node* create(tree *T,int val)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    if(temp==NULL)
    {
        printf("Malloc error\n");
        exit(0);
    }
    temp->val=val;
    temp->l=T->nil;
    temp->r=T->nil;
    temp->p=T->nil;
    temp->colour=0;    //red is default
    return temp;
}

void leftRotate(tree *T,node *x)
{
    node *y=x->r;
    x->r=y->l;

    if(y->l!=T->nil)
        y->l->p=x;

    y->p=x->p;

    if(x->p==T->nil)
        T->root=y;
    else if(x==x->p->l)
        x->p->l=y;
    else
        x->p->r=y;

    y->l=x;
    x->p=y;
}

void rightRotate(tree *T,node *x)
{
    node *y=x->l;
    x->l=y->r;

    if(y->r!=T->nil)
        y->r->p=x;

    y->p=x->p;

    if(x->p==T->nil)
        T->root=y;
    else if(x==x->p->l)
        x->p->l=y;
    else
        x->p->r=y;

    y->r=x;
    x->p=y;
}

void RG_fixup(tree *T,node *k)
{
    node *y;//uncle
    while((k!=T->root) && (k->p->colour==0))
    {
        if(k->p==k->p->p->l)
        {
            y=k->p->p->r;
            //case 2 - k's unlce is red
            if(y->colour==0)
            {
                k->p->colour=1;   //swap parent coulor
                y->p->colour=0;   //swap grandfather colour
                y->colour=1;         //swap unlcle's colour
                k=k->p->p;
                continue;
            }
            //case 4- LEFT TRIANGLE condition
            else if(k==k->p->r)
            {
                k=k->p;
                leftRotate(T,k);
            }
            //case 3-  LEFT LINE condition
            k->p->colour=1;
            k->p->p->colour=0;
            rightRotate(T,k->p->p);
        }
        else
        {
            y=k->p->p->l;
            //case 2 - k's unlce is red
            if(y->colour==0)
            {
                k->p->colour=1;   //swap parent coulor
                y->p->colour=0;   //swap grandfather colour
                y->colour=1;         //swap unlcle's colour
                k=k->p->p;
                continue;
            }
            //case 4- RIGHT TRIANGLE condition
            else if(k==k->p->l)
            {
                k=k->p;
                rightRotate(T,k);
            }
            //case 3-  RIGHT LINE condition
            k->p->colour=1;
            k->p->p->colour=0;
            leftRotate(T,k->p->p);
        }
    }
    T->root->colour=1;
}

void insertion(tree *T,int val)
{
    node *temp=T->root;
    if(T->root==T->nil)          //case 1
    {
        temp=create(T,val);
        temp->colour=1; 
        T->root=temp;
        return;
    }

    node *p=T->nil;
    temp=T->root;
    while(temp!=T->nil)
    {
        p=temp;
        if(temp->val>val)
            temp=temp->l;
        else
            temp=temp->r;
    }
    temp=create(T,val);

    if(p->val>val)
        p->l=temp;
    else
        p->r=temp;

    temp->p=p;
    RG_fixup(T,temp);
}

typedef struct ver
{
    int bd; //bd==1, black depth is the same for every node on the same level
    int col;//col=1-> any red node has only black children, col=0->red node also has a black child
    int leaf;//leaf=1 if leaf node was black
}ver;

int Bdepth(node *x,tree T,ver *v)
{
    if(x==T.nil)
    {
        if(x->colour==0)    //red
            v->leaf=0;
        return 1;
    }
    if(x->colour==0)
    {
        if(x->l->colour==0||x->r->colour==0)
            v->col=0;
    }
    int y=Bdepth(x->r,T,v),z=Bdepth(x->l,T,v);
    
    if(y!=z)        //black depth on either side does not match, so returning a greatly increased value
    {
        v->bd=0;
        return y>z?y+5:z+5;
    }

    if(x->colour==1)
        return y+1;
    else
        return y;
}

int verification(tree T)
{
    if(T.root->colour!=1)
        return 0;

    ver v;
    v.col=1;
    v.leaf=1;
    v.bd=1;     

    if((Bdepth(T.root->l,T,&v)!=Bdepth(T.root->r,T,&v)) && v.bd==0)
        return 0;
    
    if(v.col==0||v.leaf==0)
        return 0;

    return 1;      
}


int po(node *root,tree T,int *h)
{
    if(root==T.nil)
    {
        *h=1;
        return 1;
    }
    int l;
    int r;
    if(!(po(root->l,T,&l)&&po(root->r,T,&r)))
        return 0;

    if(l!=r)
        return 0;

    *h=l;  
    if(root->colour==1)
        (*h)++;
    
    return 1;
}