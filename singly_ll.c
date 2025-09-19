#include <stdio.h>
#include <stdlib.h>

struct Node{
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

    if(temp == NULL){
        printf("Heap not Allocated.\n");
        return list;
    }
    
    temp->data = data;
    temp->next = list;
    list = temp;

    return list;
}

struct Node *addAtEnd(struct Node *list, int data){
    if(list == NULL){
        list = addAtBeg(list, data);
        return list;
    }

    struct Node *ptr = list;
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));

    if(temp == NULL){
        printf("Heap not Allocated.\n");
        return list;
    }

    while(ptr->next != NULL) ptr = ptr->next;

    temp->data = data;
    temp->next = NULL;
    ptr->next = temp;

    return list;
}

struct Node *addAtPos(struct Node *list, int data, int pos){
    if(pos < 0) return list;
    if(list == NULL) return addAtBeg(list, data);
    if(pos == 0) return addAtBeg(list, data);

    struct Node *ptr = list;
    int ind = 0;

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL){
        printf("Heap not Allocated.\n");
        return list;
    }

    while(ptr->next != NULL){
        if(ind == pos-1){
            temp->data = data;
            temp->next = ptr->next;
            ptr->next = temp;

            return list;
        }

        ptr = ptr->next;
        ind++;
    }

    // insert at end
    temp->data = data;
    temp->next = NULL;
    ptr->next = temp;


    return list;
}

struct Node *deleteNode(struct Node *list, int data){
    if(list == NULL) return list;

    struct Node *ptr = list, *temp;

    // remove the first node
    if(ptr->data == data){
        temp = ptr;
        ptr = ptr->next;
        list = ptr;
        free(temp);

        return list;
    }

    // remove any other node except the first one
    while(ptr->next != NULL && ptr->next->data != data) ptr = ptr->next;

    if(ptr->next != NULL){
        temp = ptr->next;
        ptr->next = temp->next;
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
        printf("Linked list empty.\n");
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
    struct Node *temp;

    while(list != NULL){
        temp = list;
        list = list->next;
        free(temp); 
    }

    return list;
}