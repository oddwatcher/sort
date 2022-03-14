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
node *delete (node *p)
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
    p = getright(p);
    do
    {
        printf("%d,%p,%p,%p\n", p->data, p->l, p, p->r);
        p = p->l;
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
    if (L->r = R)
    {   
        if(L->data>R->data){
            int a;
            R->data = a;
            R->data = L->data;
            L->data = R->data;
        }
        return 0;
    }
    node *p = L;
    node *r;
    node *l;
    node *piller = L;
    if (L->l != NULL)
    {
        (L->l)->r = l;
    }else{

    }
    if (R->r != NULL)
    {
        (R->r)->l = r;
    }
    piller->l = L->l;
    piller->r = R->r;
    while (p != R->r)
    {
        if (p->data > piller->data)
        {
            (piller->r)->l = newnode(p->data, piller, piller->r);
            piller->r = (piller->r)->l;
        }
        else
        {
            (piller->l)->r = newnode(p->data, piller->l, piller);
            piller->l = (piller->l)->r;
        }
        p = p->r;
    }
    partition(L, piller);
    partition(R, piller);
}

/*node *partition(node* piller, node *L, node *R)
{
    node *p =L;
    if(p->data>piller->data){
        piller->r= newnode(p->data,piller,piller->r);
        p=p->r;
        L = p;
        delete(p->l);
    }else {
        p=p->r;
    }
    while(p!=piller){
        if (p->data > piller->data)
        {
        piller->r = newnode(p->data, piller, piller->r);
        p=p->r;
        delete(p->l);
        }else{
            p=p->r;
        }
    }
    p=R;
    if(p->data<piller->data){
        piller->l= newnode(p->data,piller->l,piller);
        p=p->l;

        if (p->data < piller)
        {
            piller->l = newnode(p->data, piller->l, piller);
        }

}*/
node *quicksort(node *p)
{
    p = getleft(p);
    partition(p->r, getright(p));
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
