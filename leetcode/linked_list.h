#include <stdio.h>
typedef struct linked_list
{
    int val;
    struct linked_list *next;
} LinkedNode;

void print_list(LinkedNode* head) {
    LinkedNode *p = head;
    while(p != NULL) {
        printf("-> %d ", p->val);
        p = p->next;
    }
    printf("\n");
}