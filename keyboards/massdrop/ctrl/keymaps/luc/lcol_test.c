#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "lcol.h"

void lambda(lcol_node *n, void *userdata)
{
    printf("node value is %ld\n", (long int)(n->data));
}

void lambda_sum(lcol_node *n, void *userdata)
{
    *(long int*)userdata += (long int)n->data;
}

void main()
{
    printf("sizeof(void*) = %ld\n", sizeof(void*));
    printf("sizeof(int)   = %ld\n", sizeof(int));

    lcol_list *l = lcol_list_new();
    printf("lcol_list *l = %p\n", l);

    lcol_list_push(l, (void*)1);
    lcol_list_push(l, (void*)1);
    lcol_list_push(l, (void*)2);
    lcol_list_push(l, (void*)3);
    lcol_list_push(l, (void*)5);
    lcol_list_push(l, (void*)8);
    lcol_list_foreach(l, lambda, NULL);

    long int sum = 0;
    lcol_list_foreach(l, lambda_sum, &sum);
    printf("summed value is %ld\n", sum);

    lcol_list_delete(l);
}
