#include <stdio.h>
#include <stdlib.h>
#ifndef node
typedef struct node
{
    struct node *l;
    struct node *r;
    int key;
} node;
#endif

node *newnode(int key, node *l, node *r)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->key = key;
    temp->l = l;
    temp->r = r;
    return temp;
}

void deletenode (node *p)
{
    if (p->l != NULL)
    {
        (p->l)->r = p->r;
    }
    if (p->r != NULL)
    {
        (p->r)->l = p->l;
    }
    printf("Deleting:%p:%d\n", p, p->key);
    free(p);
}

node *getright(node *p)
{
    while (p->r != NULL)
    {
        p = p->r;
    }
    return p;
}

node *getleft(node *p)
{
    while (p->l != NULL)
    {
        p = p->l;
    }
    return p;
}

void output(node *p)
{
    p = getleft(p);
    do
    {
        printf("%d,%p,%p,%p\n", p->key, p->l, p, p->r);
        p = p->r;
    } while (p != NULL);
}

node *scan()
{
    int d;
    int i;
    printf("input number of numbers:");
    scanf("%d", &i);
    node *H = newnode(0, NULL, NULL);
    for (; i > 0; i--)
    {
        H->r = newnode(0, H, NULL);
        H = H->r;
        scanf("%d", &(H->key));
        printf("%d,%p,%p,%p\n", H->key, H->l, H, H->r);
    }
    return H;
}
node *bubble(node *p)
{
    int flag;
    int t;
    node *H = getright(p);
    p = H;
    flag = 1;
    while (flag != 0)
    {
        flag = 0;
        while (p->l != NULL)
        {
            t = p->key;
            p = p->l;
            if (p->key < t)
            {
                (p->r)->key = p->key;
                p->key = t;
                flag = 1;
            }
        }
        p = H;
    }
    return H;
}

node *getM(node *p)
{
    p = getleft(p);
    int d = p->key;
    int D = p->key;
    node *max = p;
    node *min = p;
    while (p != NULL)
    {
        if (d < p->key)
        {
            d = p->key;
            max = p;
        }
        if (D > p->key)
        {
            D = p->key;
            min = p;
        }
        p = p->l;
    }
    return newnode((D + d) / 2, max, min);
}
int partition(node *L, node *R)
{
	printf("part\n");
	if(L==R){
		return 0;}

        if(L->key>R->key){
            int a;
	    a = R->key;
            R->key = L->key;
            L->key = a;
        }
// check if only consists two elements between L&R 
	if(L->r==R){
		return 0;
	}


// establish a new chain and attach it to orignal chain
// notice L&R will not be replaced to ensure the program won't lost track of chain
    node *p = L->r; //used to climb over unsorted part
    node *piller = newnode(L->key,NULL,NULL);//use Left of chain as piller
    node *r = newnode(0,piller,R);//marks the left and right of the new chain but not intend to replace R&L
    node *l = newnode(0,L,piller);//and attach it to original chain
    piller->l = l; 
    piller->r = r;// L<-l<->piller<->r->R
//New idea is just use l&r as begining of the addition,after make sure of their position

    while (p != R)//insert elements from former chain to new chain,between l _ piller ,piller _ r p goes from left to right
    {
        if (p->key > piller->key)
        {
            r->l = newnode(p->key, r->l, r);
            ((r->l)->l)->r = r->l;
        }
        else
        {
            l->r = newnode(p->key,l,l->r);
	    ((l->r)->r)->l = l->r; 
        }
        p = p->r;
    }
    p = L->r;
    //remove former chain elements between L&R
    while(p!=R){
	    p = p->r;
	    free(p->l);
    }
    deletenode(l);
    deletenode(r);
    L = L->r;
    deletenode(L->l);

    // recursion partition to achieve quicksort
    if(piller!=L&&piller->l){
	    partition(L,piller->l);}
    if(piller!=R){
	    partition(piller->r,R);}
    return 0;
}

node *quicksort(node *p)
{
    partition(getleft(p), getright(p));
    return p;
}

