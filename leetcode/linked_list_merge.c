#include "linked_list.h"
#include <stdio.h>

/* 有序链表合并 */
LinkedNode* merge_sorte_list2(LinkedNode* list1, LinkedNode* list2, LinkedNode* target);

int main(int argc, char* argv[]) {
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

    node1.next = &node3;
    node3.next = &node5;
    node5.next = &node7;
    node7.next = NULL;

    node2.next = &node4;
    node4.next = NULL;
    //node6.next = NULL;
    //node8.next = NULL;

    LinkedNode target;
    LinkedNode* head = merge_sorte_list2(&node1, &node2, &target);
    print_list(head);
    
}

LinkedNode* merge_sorte_list2(LinkedNode* list1, LinkedNode* list2, LinkedNode* target) {
    if (NULL == list1) {
        return list2;
    }
    if (NULL == list2) {
        return list1;
    }
    LinkedNode* p1 = list1;
    LinkedNode* p2 = list2;
    LinkedNode* tail = target;
    while (p1 != NULL && p2 != NULL) {
        if (p1->val < p2->val) {
            tail->next = p1;
            tail = tail->next;
            p1 = p1->next;
        } else {
            tail->next = p2;
            tail = tail->next;
            p2 = p2->next;
        }
    }
    if (NULL != p1) {
        tail->next = p1;
    }
    if (NULL != p2) {
        tail->next = p2;
    }
    return target->next;

}