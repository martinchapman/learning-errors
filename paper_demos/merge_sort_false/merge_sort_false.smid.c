#include <stdlib.h>

unsigned int __CPROVER_unwind_limit=2;
unsigned int __CPROVER_unwind_count;

struct node {
    struct node     *next;
    int             value;
};

struct list {
    struct node     *slist;
    struct list     *next;
};

static void merge_single_node(struct node ***dst,
                              struct node **data)
{
    // pick up the current item and jump to the next one
    struct node *node = *data;
    *data = node->next;
    node->next = NULL;

    // insert the item into dst and move cursor
    **dst = node;
    *dst = &node->next;
}

static void merge_pair(struct node **dst,
                       struct node *sub1,
                       struct node *sub2)
{
    // merge two sorted sub-lists into one
    __CPROVER_unwind_count=0;
    while ((++__CPROVER_unwind_count < __CPROVER_unwind_limit) && (sub1 || sub2)) {
        if (!sub2 || (sub1 && sub1->value < sub2->value))
            merge_single_node(&dst, &sub1);
        else
            merge_single_node(&dst, &sub2);
    }
}

static struct list* seq_sort_core(struct list *data)
{
    struct list *dst = NULL;

    __CPROVER_unwind_count=0;
    while (++__CPROVER_unwind_count < __CPROVER_unwind_limit && nondet_int()) {
        struct list *next = data->next;
        if (!next) {
            // take any odd/even padding as it is
            data->next = dst;
            dst = data;
            break;
        }

        // take the current sub-list and the next one and merge them into one
        merge_pair(&data->slist, data->slist, next->slist);
        data->next = dst;
        dst = data;

        // free the just processed sub-list and jump to the next pair
        data = next->next;
        //free(next);
    }

    return dst;
}

static void inspect_before(struct list *shape)
{
    /* we should get a list of sub-lists of length exactly one */
    //assert(shape);

    for (__CPROVER_unwind_count=1; __CPROVER_unwind_count < __CPROVER_unwind_limit && shape->next; ++__CPROVER_unwind_count, shape = shape->next) {
        //assert(shape);
        //assert(shape->next);
        //assert(shape->slist);
        //assert(shape->slist->next == NULL);
    }

    /* check the last node separately to make the exercising more fun */
    //assert(shape);
    //assert(shape->next == NULL);
    //assert(shape->slist);
    //assert(shape->slist->next == NULL);
}

static void inspect_after(struct list *shape)
{
    /* we should get exactly one node at the top level and one nested list */
    //assert(shape);
    //assert(shape->next == NULL);
    //assert(shape->slist != NULL);

    /* the nested list should be zero terminated (iterator back by one node) */
    struct node *pos;
    for (__CPROVER_unwind_count=1, pos = shape->slist; __CPROVER_unwind_count < __CPROVER_unwind_limit && pos->next; ++__CPROVER_unwind_count, pos = pos->next);
    //assert(!pos->next);
}

int main()
{
    struct list *data = NULL;
    __CPROVER_unwind_count=0;
    while (++__CPROVER_unwind_count < __CPROVER_unwind_limit && nondet_int()) {
        struct node *node = malloc(sizeof *node);
        if (!node)
            abort();

        node->next = node;
        node->value = nondet_int();

        struct list *item = malloc(sizeof *item);
        if (!item)
            abort();

        item->slist = node;
        item->next = data;
        data = item;
    }

    //if (!data)
        //return EXIT_SUCCESS;

    inspect_before(data);

    // do O(log N) iterations
    __CPROVER_unwind_count=0;
    while (++__CPROVER_unwind_count < __CPROVER_unwind_limit && nondet_int())
        data = seq_sort_core(data);

    inspect_after(data);

    struct node *node = data->slist;
    //free(data);

    __CPROVER_unwind_count=0;
    while (++__CPROVER_unwind_count < __CPROVER_unwind_limit && node) {
        struct node *snext = node->next;
        //free(node);
        node = snext;
    }

    _Learn_assert(0 == 1);
    return EXIT_SUCCESS;
}
