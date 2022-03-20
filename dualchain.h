#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *l;
    struct node *r;
} node;

node *newnode(int data, node *l, node *r)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->l = l;
    new->r = r;
    return new;
}
void delete (node *p)
{
    if (p->l != NULL)
    {
        (p->l)->r = p->r;
    }
    if (p->r != NULL)
    {
        (p->r)->l = p->l;
    }
    printf("Deleting:%p:%d\n", p, p->data);
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
        printf("%d,%p,%p,%p\n", p->data, p->l, p, p->r);
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
        scanf("%d", &(H->data));
        printf("%d,%p,%p,%p\n", H->data, H->l, H, H->r);
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
            t = p->data;
            p = p->l;
            if (p->data < t)
            {
                (p->r)->data = p->data;
                p->data = t;
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
    int d = p->data;
    int D = p->data;
    node *max = p;
    node *min = p;
    while (p != NULL)
    {
        if (d < p->data)
        {
            d = p->data;
            max = p;
        }
        if (D > p->data)
        {
            D = p->data;
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

        if(L->data>R->data){
            int a;
	    a = R->data;
            R->data = L->data;
            L->data = a;
        }
// check if only consists two elements between L&R 
	if(L->r==R){
		return 0;
	}


// establish a new chain and attach it to orignal chain
// notice L&R will not be replaced to ensure the program won't lost track of chain
    node *p = L->r; //used to climb over unsorted part
    node *piller = newnode(L->data,NULL,NULL);//use Left of chain as piller
    node *r = newnode(0,piller,R);//marks the left and right of the new chain but not intend to replace R&L
    node *l = newnode(0,L,piller);//and attach it to original chain
    piller->l = l; 
    piller->r = r;// L<-l<->piller<->r->R
//New idea is just use l&r as begining of the addition,after make sure of their position

    while (p != R)//insert elements from former chain to new chain,between l _ piller ,piller _ r p goes from left to right
    {
        if (p->data > piller->data)
        {
            r->l = newnode(p->data, r->l, r);
            ((r->l)->l)->r = r->l;
        }
        else
        {
            l->r = newnode(p->data,l,l->r);
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
    delete(l);
    delete(r);
    L = L->r;
    delete(L->l);

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

int main()
{
    node *A = scan();
    A = bubble(A);
    output(A);
    A = scan();
    A = quicksort(A);
    output(A);
}
