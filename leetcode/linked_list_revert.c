#include<stdio.h>

typedef struct linked_list
{
    int val;
    struct linked_list *next;
} LinkedNode;

LinkedNode* revertList(LinkedNode *head);

int main(int argc, char* argv[]) {
    LinkedNode listNode1;
    listNode1.val = 1;
    
    LinkedNode listNode2;
    listNode2.val = 2;

    LinkedNode listNode3;
    listNode3.val = 3;

    listNode1.next = &listNode2;
    listNode2.next = &listNode3;
    listNode3.next = NULL;

    LinkedNode *p = &listNode1;
    while(p!= NULL) {
        printf("this node val %d\n", p->val);
        p = p->next;
    }

    printf("now revert...\n");
    LinkedNode *res = revertList(&listNode1);
    p = res;
    while(NULL != p) {
        printf("this node val %d\n", p->val);
        p = p->next;
    }
    return 0;
}

LinkedNode* revertList(LinkedNode *head) {
    if (NULL == head) {
        return NULL;
    }
    LinkedNode *resHead = head;
    LinkedNode *currentNode = head->next;
    resHead->next = NULL;
    while (NULL != currentNode) {
        LinkedNode *p = currentNode->next;
        currentNode->next = resHead;
        resHead = currentNode;

        currentNode = p;
    }
    
    return resHead;
}
