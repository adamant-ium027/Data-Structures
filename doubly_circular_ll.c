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

int main(void){

    return 0;
}

struct Node *addAtBeg(struct Node *list, int data){
    if(list == NULL){
        struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
        MEM_ASSIGN_CHECK(temp)
        temp->data = data;
        temp->prev = temp;
        temp->next = temp;
        list = temp;
        return list;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->prev = list;
    temp->next = list->next;
    list->next->prev = temp;
    list->next = temp;

    return list;
}

struct Node *addAtEnd(struct Node *list, int data){
    if(list == NULL) return addAtBeg(list, data);

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->prev = list;
    temp->next = list->next;
    list->next = temp;
    temp->next->prev = temp;
    list = temp;
    
    return list;
}

struct Node *addAtPos(struct Node *list, int data, int pos){
    if(pos < 0) return list; // if given position is negative
    if(list == NULL) return addAtBeg(list, data); // if there is no node and pos value if +ve
    if(pos == 0) return addAtBeg(list, data); // if need to insert the node as the first node

    struct Node *ptr = list->next;
    int ind = 1;

    while(ptr != list){
        if(ind == pos){
            struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
            MEM_ASSIGN_CHECK(temp);
            temp->data = data;
            temp->prev = ptr;
            temp->next = ptr->next;
            ptr->next->prev = temp;
            ptr->next = temp;
            return list;
        }

        ptr = ptr->next;
        ind++;
    }

    return addAtEnd(list, data);
}

struct Node *deleteNode(struct Node *list, int data){
    if(list == NULL) return list; // if list is empty
    if(list->next == list && list->data == data){ // is list has only 1 node and it is to be deleted
        free(list);
        return NULL;
    }

    struct Node *ptr = list->next, *temp;
    while(ptr != list){
        if(ptr->data == data){
            temp = ptr;
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            free(temp);
            return list;
        }

        ptr = ptr->next;
    }

    if(ptr->data == data){
        temp = ptr;
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        list = temp->prev;
        free(temp);
    }

    return list;
}

int searchNode(struct Node *list, int data){
    if(list == NULL) return -1;
    
    struct Node *ptr = list->next;
    int pos = 0;

    do{
        if(ptr->data == data) return pos;
        ptr = ptr->next;
        pos++;
    }while(ptr != list->next);

    return -1;
}

void printList(struct Node *list){
    if(list == NULL){
        printf("List is empty.\n");
        return;
    }

    struct Node *ptr = list->next;
    while(ptr != list){
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }

    printf("%d\n", ptr->data);
}

struct Node *freeList(struct Node *list){
    if(list == NULL) return list;

    struct Node *ptr = list->next, *temp;
    while(ptr != list){ // remove n-1 nodes
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    free(list); // remove last node
    return NULL;
}