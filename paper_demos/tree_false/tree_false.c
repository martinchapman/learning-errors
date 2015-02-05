#include <stdlib.h>

/* Builds a tree with parent links and
 * checks whether the values are still correct.
 */

static void fail(void) {
ERROR:
    goto ERROR;
}

#define ___MY_ASSERT(cond) do {     \
if (!(cond))                    \
fail();                     \
} while (0)

struct node {
    struct node     *left;
    struct node     *right;
    struct node     *parent;
    int             value;
};

static void inspect(struct node *node)
{
    //assert(node);
    while (node != NULL) {
        if (node->left)
            //assert(node->left->value == 42);
        //assert(node->value);
        node = node->parent;
    }
}

void if_line_42() {

    
    
}

struct node *create_tree()
{
    struct node *nodelast = NULL;
    struct node *node = NULL;
    while (nondet_int()) {
        node = malloc(sizeof *node);
        //if (!node)
            //abort();
        
        node->left = NULL;
        node->right = nodelast;
        if (nodelast)
            nodelast->parent = node;
        int value = nondet_int();
        node->value = value;
        nodelast = node;
    }
    while (node != NULL) {
        node->left = malloc(sizeof *node);
        //if (!node)
            //abort();
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->value = 42;
        node->left->parent = node;
        node = node->right;
    }
    return nodelast;
}

void free_tree(struct node *node) {
    while (1) {
        if (node->right == NULL)
            break;
        node = node->right;
    }
    while (node != NULL) {
        if (node->left)
            //free(node->left);
        if (node->right)
            //free(node->right);
        node = node->parent;
    }
}

int main()
{
    struct node *data = create_tree();
    
    //if (!data)
        //return EXIT_SUCCESS;
    
    inspect(data);
    
    free_tree(data);
    
    _Learn_assert(0 == 1);
    return EXIT_SUCCESS;
}
