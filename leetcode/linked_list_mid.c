#include "linked_list.h"

LinkedNode* find_mid(LinkedNode* head);

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

    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node7;
    node7.next = &node8;
    node8.next = NULL;

    LinkedNode* p = find_mid(&head);

    printf("mid node is %d\n", p->val);
    return 0;
}

LinkedNode* find_mid(LinkedNode* head) {
    if(NULL == head || NULL == head->next) {
        return head;
    }
    LinkedNode* p = head;
    LinkedNode* p_2 = head;
    while(NULL != p_2 && NULL != p_2->next) {
        p = p->next;
        p_2 = p_2->next->next;
    }
    return p;
}