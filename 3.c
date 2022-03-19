#include "node.h"
node *insertL(node *c, node *p)
{
    if (p->l != NULL)
    {
        (p->l)->r = p->r;
    }
    if (p->r != NULL)
    {
        (p->r)->l = p->l;
    }
    //remove p from the chain and attach it to a new position
    node *pr = p->r;
    p->l=c->l;
    p->r=c;
    c->l=p;
    if (p->l != NULL)
    {
        (p->l)->r = p;
    }
    return pr;
}
node *merge(node *A, node *B, node *AR, node *BR)
{
    node *p = A;
    BR = BR->r;
    while (1)
    {
        if (p->key >= B->key)
        {

            B = insertL(p, B);
            if (B == BR)
            {
                break;
            }
        }
        else
        {
            if (p != AR)
            {
                p = p->r;
            }
            else
            {
                if (B->key > p->key)
                {
                    BR->r = AR->r;
                    AR->r = B;
                    B->l = AR;
                    if (BR->r != NULL)
                    {
                        (BR->r)->l = BR;
                    }
                    return BR;
                }
            }
        }
    }
    return AR;
}

node *getsorted(node *p)
{
    node *temp;
    while (1)
    {
        temp = p;
        p = p->r;
        if (p != NULL)
        {
            if (p->key < temp->key)
            {
                return temp;
            }
        }
        else
        {
            return temp;
        }
    }
}

node *mergesort(node *p, node *end)
{
    p = getleft(p);
    node *A = p;
    node *B;
    node *AR;
    node *BR;
    while (1)
    {
        AR = getsorted(A);
        B = AR->r;
        if(B==NULL){
            return AR;
        }
        BR = getsorted(B);
        p = merge(A, B, AR, BR);
    }
}
int main()
{
    node *A = scan();
    // A = bubble(A);
    // output(A);
    // A = scan();
    // A = quicksort(A);
    // output(A);
    // A = scan();
    /*node* B = scan();
    A = getleft(A);
    B = getleft(B);
    A = merge(A->r,B->r,getright(A),getright(B));
    output(A);*/
    /*node*B = getsorted(getleft(A));
    outputR(B);*/
    A = mergesort(A, getright(A));
    getleft(A);
    output(A);
    return 0;
}