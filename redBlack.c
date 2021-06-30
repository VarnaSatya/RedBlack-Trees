#include<stdio.h>
#include<stdlib.h>
#include"header.h"

int duplicate(int *a,int i,int y)
{
    int j;
    for(j=0;j<=i;j++)
        if(a[j]==y)
            return 1;
    return 0;
}

int main()
{
    tree T;
    
    T.nil=(node*)malloc(sizeof(node));
    T.nil->l=NULL;
    T.nil->r=NULL;
    T.nil->p=NULL;
    T.nil->val=-1;
    T.root=T.nil;

    //for hardcoded input
    int a[]={41, 38, 31, 12, 19, 8},x=6,i;

     
     //for random input of elements
      /*
    int *a,x,i,y;
    printf("Enter the number of array elements\n");
    scanf("%d",&x);
    a=(int*)malloc(sizeof(int)*x);

    for(i=0;i<x;)
    {
        y=rand();
        if(!duplicate(a,i,y))   //to prevent duplicate entries
            i++;
    }
    printf("\n");
      */

    int h;
    for(i=0;i<x;i++)
    {
        insertion(&T,a[i]);
        printf("On inserting %d:\n",a[i]);
        if(verification(T)==1)
            printf("VALID\n");
        else
            printf("INVALID\n");

        h=0;    //black height is updated to variable h
        if(po(T.root,T,&h)) //po return 1 if black height is the same, 0 if it is not the same
            printf("VALID\n");
        else
            printf("INVALID\n");

        printf("Black height: %d\n",h);
        disp(T,T.root);
        printf("\n");
    }
    //printf("%d %s\n",T.root->val,T.root->colour==0?"red":"black");
    
}