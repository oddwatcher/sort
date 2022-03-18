#include"node.h"

int main()
{
    node *A = scan();
    A = bubble(A);
    output(A);
    A = scan();
    A = quicksort(A);
    output(A);
    return 0;
}