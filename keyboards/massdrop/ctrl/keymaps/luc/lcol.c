#include "lcol.h"

static void list_free_items(lcol_list *l);

lcol_node* lcol_node_alloc()
{
    lcol_node *node = malloc(sizeof(lcol_node));
    node->data = NULL;
    node->next = NULL;

    return node;
}

void lcol_node_free(lcol_node *n)
{
    free(n);
}

lcol_list* lcol_list_new()
{
    lcol_list* list = malloc(sizeof(lcol_list));
    list->head = NULL;

    return list;
}

void lcol_list_delete(lcol_list *l)
{
    list_free_items(l);
    free(l);
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

void lcol_list_clear(lcol_list *l)
{
    list_free_items(l);
    l->head = NULL;
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

static void list_free_items(lcol_list *l)
{
    lcol_node *node = l->head;
    lcol_node *next;
    while (node != NULL)
    {
        next = node->next;
        lcol_node_free(node);
        node = next;
    }
}
