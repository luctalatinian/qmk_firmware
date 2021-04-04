#include "lcol.h"

lcol_node* lcol_node_alloc()
{
    return (lcol_node*)malloc(sizeof(lcol_node));
}

void lcol_node_free(lcol_node *n)
{
    free(n);
}

lcol_list* lcol_list_new()
{
    return (lcol_list*)malloc(sizeof(lcol_list));
}

void lcol_list_push(lcol_list *l, void *data)
{
    lcol_node *node = lcol_node_alloc();
    node->data = data;

    lcol_node **tail = &l->head;
    while (*tail != NULL)
        tail = &(*tail)->next;

    *tail = node;
}

void lcol_list_delete(lcol_list *l)
{
    lcol_node *node = l->head;
    lcol_node *next;
    while (node != NULL)
    {
        next = node->next;
        lcol_node_free(node);
        printf("free node\n");
        node = next;
    }

    free(l);
}

void lcol_list_foreach(lcol_list *l, lcol_lambda fn, void *userdata)
{
    lcol_node *node = l->head;
    while (node != NULL)
    {
        fn(node, userdata);
        node = node->next;
    }
}
