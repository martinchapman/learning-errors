/*
 * This source code is licensed under the GPL license, see License.GPLv2.txt
 * for details.  The list implementation is taken from the Linux kernel.
 */

#include <stdbool.h>
#include <stdlib.h>
//#include <stdio.h>

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->next = (ptr); \
} while (0)

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

struct node {
    int                         value;
    struct list_head            linkage;
    struct list_head            nested;
};

LIST_HEAD(gl_list);

static void inspect(const struct list_head *head)
{
    // check the head

    //assert(head);
    //assert(head->next != head);
    //assert(head->prev != head);

    // go one step backward
    head = head->prev;
    //assert(head);
    //assert(head->next != head);
    //assert(head->prev != head);

    // resolve root
    const struct node *node = list_entry(head, struct node, linkage);
    //assert(node);
    //assert(node->nested.next == &node->nested);
    _Learn_assert(node->nested.prev == &node->nested);
    //_Learn_assert(false);
    //assert(node->nested.next != &node->linkage);
    //assert(node->nested.prev != &node->linkage);

    // check some properties
    /*assert(node != (const struct node *)head);
    assert(node != (const struct node *)&node->linkage);
    assert(node == (const struct node *)&node->value);
    assert(head == node->linkage.next->prev);
    assert(head == node->linkage.prev->next);*/

    // check traversal
    for (head = head->next; &node->linkage != head; head = head->next);

     //assert(list_entry(head, struct node, linkage) == node);
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add(list, head);
}

static void gl_insert(int value)
{
    struct node *node = malloc(sizeof *node);
    //if (!node)
        //abort();

    node->value = value;
    list_add(&node->linkage, &gl_list);
    INIT_LIST_HEAD(&node->nested);
}

static void gl_read()
{
    do {
        gl_insert(nondet_int());
    }
    while (nondet_int());
}

static void gl_destroy()
{
    struct list_head *next;
    while (&gl_list != (next = gl_list.next)) {
        gl_list.next = next->next;
        //free(list_entry(next, struct node, linkage));
	  }
}

static int val_from_node(struct list_head *head) {
    struct node *entry = list_entry(head, struct node, linkage);
    return entry->value;
}

static bool gl_sort_pass()
{
    bool any_change = false;

    struct list_head *pos0 = gl_list.next;
    struct list_head *pos1;
    while (&gl_list != (pos1 = pos0->next)) {
        const int val0 = val_from_node(pos0);
        const int val1 = val_from_node(pos1);
        if (val0 <= val1) {
            // jump to next
            pos0 = pos1;
            continue;
        }

        any_change = nondet_bool();
        list_move(pos0, pos1);
    }

    return any_change;
}

static void gl_sort()
{
    while (gl_sort_pass())
        ;
}

int main()
{
	int __CPROVER_nondet_exit;
	if (__CPROVER_nondet_exit) {
		return 0;
	}
    gl_read();
    inspect(&gl_list);

    gl_sort();
    inspect(&gl_list);

    gl_destroy();

		// _Learn_assert(false);

    return 0;
}
