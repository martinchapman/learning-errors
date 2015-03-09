#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

/*static void fail(void) {
ERROR:
    goto ERROR;
}

#define ___SL_ASSERT(cond) do {     \
    if (!(cond))                    \
        fail();                     \
} while (0)*/

#define ___SL_ASSERT(cond) do {     \
	    if (!(cond))                \
	        goto learn_error;               \
} while (0)

#ifndef PREDATOR
#   define ___sl_plot(...) do { } while (0)
#endif

struct node {
    struct node *next;
    struct node *prev;
};

static struct node* alloc_node(void)
{
    struct node *ptr = malloc(sizeof *ptr);
    if (!ptr)
        abort();

    ptr->next = NULL;
    ptr->prev = NULL;
    return ptr;
}

static void chain_node(struct node **ppnode)
{
    struct node *node = alloc_node();
    node->next = *ppnode;
    *ppnode = node;
}

static struct node* create_sll(const struct node **pp1, const struct node **pp2)
{
    struct node *list = NULL;

    do
        chain_node(&list);
    while (__VERIFIER_nondet_int());

    *pp2 = list;

    while (__VERIFIER_nondet_int())
        chain_node(&list);

    *pp1 = list;

    do
        chain_node(&list);
    while (__VERIFIER_nondet_int());

    return list;
}

void init_back_link(struct node *list) {
    for (;;) {
        struct node *next = list->next;
        if (!next)
            return;

        next->prev = list;
        list = next;
    }
}

void reverse_dll(struct node *list) {
    while (list) {
        struct node *next = list->next;
        list->next = list->prev;
        list->prev = next;
        list = next;
    }
}

void remove_fw_link(struct node *list) {
    while (list) {
        struct node *next = list->next;
        list->next = NULL;
        list = next;
    }
}

int check_seq_next(const struct node *beg, const struct node *const end) {
    ___SL_ASSERT(beg);
    ___SL_ASSERT(end);

    for (beg = beg->next; end != beg; beg = beg->next)
        ___SL_ASSERT(beg);

    return 0;
    learn_error:
	return 1;
}

int check_seq_prev(const struct node *beg, const struct node *const end) {
    ___SL_ASSERT(beg);
    ___SL_ASSERT(end);

    for (beg = beg->prev; end != beg; beg = beg->prev)
        ___SL_ASSERT(beg);

    return 0;
    learn_error:
	return 1;
}

int main()
{
	int __CPROVER_error = 0;
    const struct node *p1, *p2;

    struct node *list = create_sll(&p1, &p2);
    ___sl_plot(NULL, &list, &p1, &p2);
    ___SL_ASSERT(check_seq_next(p1, p2) == 0);
    ___SL_ASSERT(!p1->prev);
    ___SL_ASSERT(!p2->prev);

    init_back_link(list);
    ___sl_plot(NULL, &list, &p1, &p2);
    ___SL_ASSERT(check_seq_next(p1, p2) == 0);
    ___SL_ASSERT(check_seq_prev(p2, p1) == 0);

    reverse_dll(list);
    ___sl_plot(NULL, &list, &p1, &p2);
    ___SL_ASSERT(check_seq_prev(p1, p2) == 0);
    ___SL_ASSERT(check_seq_next(p2, p1) == 0);

    remove_fw_link(list);
    ___sl_plot(NULL, &list, &p1, &p2);
    ___SL_ASSERT(check_seq_prev(p1, p2) == 0);

    while (list) {
        struct node *prev = list->prev;
        free(list);
        list = prev;
    }

    return 0;
    learn_error:
	_Learn_assert(0 == 1);
	return 1;
}
