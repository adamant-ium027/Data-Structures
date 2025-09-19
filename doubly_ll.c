#include <stdio.h>
#include <stdlib.h>
#define MEM_ASSIGN_CHECK(temp) if(temp == NULL){ printf("Heap not Allocated.\n"); return list; }

struct Node{
    struct Node *prev;
    int data;
    struct Node *next;
};

struct Node *addAtBeg(struct Node *, int);
struct Node *addAtEnd(struct Node *, int);
struct Node *addAtPos(struct Node *, int, int);
struct Node *deleteNode(struct Node *, int);
int searchNode(struct Node *, int);
void printList(struct Node *);
struct Node *freeList(struct Node *);

struct Node *addAtBeg(struct Node *list, int data){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->prev = NULL;
    temp->next = list;

    if(list != NULL) list->prev = temp; // if initally the list was not empty then just add the temp node to the original list head.

    return temp;
}

struct Node *addAtEnd(struct Node *list, int data){
    if(list == NULL){
        list = addAtBeg(list, data);
        return list;
    }

    struct Node *ptr = list;
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)

    while(ptr->next != NULL) ptr = ptr->next;
    temp->data = data;
    temp->prev = ptr;
    temp->next = NULL;
    ptr->next = temp;

    return list;
}


struct Node *addAtPos(struct Node *list, int data, int pos){
    if(pos < 0) return list;
    if(list == NULL) return addAtBeg(list, data);
    else if(pos == 0) return addAtBeg(list, data);

    struct Node *ptr = list;
    int ind = 1;

    while(ptr->next != NULL){
        if(ind == pos){
            struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
            MEM_ASSIGN_CHECK(temp)
            temp->data = data;
            temp->prev = ptr;
            temp->next = ptr->next;
            ptr->next->prev = temp;
            ptr->next = temp;
            return list;
        }

        ind++;
        ptr = ptr->next;
    }

    // add the node at last of the list if the pos value if = or > than the length of the list
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->prev = ptr;
    temp->next = NULL;
    ptr->next = temp;

    return list;
}

struct Node *deleteNode(struct Node *list, int data){
    if(list == NULL) return NULL; // if list is empty
    if(list->data == data && list->next == NULL){ // if list has only one node and the 1st node needs to be deleted.
        free(list);
        return NULL;
    }
    else if(list->data == data && list->next != NULL){ // if list has more than 1 nodes and the 1st node needs to be deleted.
        struct Node *temp = list;
        list = list->next;
        list->prev = NULL;
        free(temp);
        return list;
    }

    struct Node *ptr = list;
    while(ptr != NULL && ptr->data != data) ptr = ptr->next;

    if(ptr != NULL && ptr->next != NULL){ // if any other node is to be deleted but not the last one.
        struct Node *temp;
        temp = ptr;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        free(temp);
    }
    else if(ptr != NULL && ptr->next == NULL){// if last node is to be deleted.
        struct Node *temp = ptr;
        ptr->prev->next = ptr->next;
        free(temp);
    }

    return list;
}

int searchNode(struct Node *list, int data){
    struct Node *ptr = list;
    int pos = 0;

    while(ptr != NULL){
        if(ptr->data == data) return pos;
        ptr = ptr->next;
        pos++;
    }

    return -1;
}

void printList(struct Node *list){
    if(list == NULL){
        printf("List is empty.\n");
        return;
    }

    struct Node *ptr = list;
    while(ptr != NULL){
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

struct Node *freeList(struct Node *list){
    struct Node *ptr = list, *temp;

    while(ptr != NULL){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    return NULL;
}