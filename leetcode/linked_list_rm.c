#include "linked_list.h"

/* 删除倒第N个节点 */

LinkedNode* rm_n(LinkedNode* head, int n);

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
    node9.next = NULL;
    LinkedNode* res = rm_n(&head, 1);

    print_list(res);
}

LinkedNode* rm_n(LinkedNode* head, int n) {
    if (NULL == head) {
        return NULL;
    }
    // length of list
    int len = 0;
    LinkedNode* p = head;
    while(NULL != p) {
        len++;
        p = p->next;
    }
    if (len < n) {
        return NULL;
    }
    if (len == n) {
        LinkedNode* res = head;
        res = head->next;
        head->next = NULL;
        return res;
    }
    // num of node
    LinkedNode* p_n_pre = head;
    for(int i = 1; i < len - n; i++) {
        p_n_pre = p_n_pre->next;
    }
    // rm
    p = p_n_pre->next;
    p_n_pre->next = p->next;
    p->next = NULL;
    return head;
}