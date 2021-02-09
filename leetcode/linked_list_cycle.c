#include "linked_list.h"
#include <stdio.h>

LinkedNode* findCycleEntry(LinkedNode *head);

int main(int argc, char* argv[]) {
    LinkedNode head;
    head.val = 0;

    LinkedNode node1;
    node1.val = 1;

    LinkedNode node2;
    node2.val = 2;

    LinkedNode node3;
    node3.val = 3;

    LinkedNode node4;
    node4.val = 4;

    LinkedNode node5;
    node5.val = 5;

    LinkedNode node6;
    node6.val = 6;

    LinkedNode node7;
    node7.val = 7;

    LinkedNode node8;
    node8.val = 8;

    LinkedNode node9;
    node9.val = 9;

    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node7;
    node7.next = &node8;
    node8.next = &node9;
    node9.next = &node4;

    LinkedNode *p = findCycleEntry(&head);
    printf("cycle start is %d\n", p->val);
    return 0;
}

LinkedNode* findCycleEntry(LinkedNode *head) {
    if (NULL == head) {
        return NULL;
    }

    LinkedNode *fastP = head;
    LinkedNode *slowP = head;
    while(1) {
        if (fastP == NULL || fastP->next == NULL) {
            // no cycle
            return NULL;
        }
        fastP = fastP->next->next;
        slowP = slowP->next;
        if (fastP == slowP) {
            break;
        }
    }

    LinkedNode *p = head;
    LinkedNode *c = slowP;
    while(1) {
        if (p == c) {
            return p;
        }
        p = p->next;
        c = c->next;
    }
    return NULL;

}