#include <stddef.h>
#include <stdlib.h>

//
typedef struct lcol_node
{
    void             *data;
    struct lcol_node *next;
} lcol_node;

lcol_node* lcol_node_alloc (void);

void       lcol_node_free  (lcol_node *n);

//
typedef struct
{
    lcol_node *head;
} lcol_list;

//
typedef
void       (*lcol_lambda)      (lcol_node *n, void *userdata);

lcol_list* lcol_list_new       (void);

void       lcol_list_delete    (lcol_list*);

void       lcol_list_push      (lcol_list*, void *data);

void       lcol_list_clear     (lcol_list*);

void       lcol_list_foreach   (lcol_list*, lcol_lambda fn, void *userdata);
