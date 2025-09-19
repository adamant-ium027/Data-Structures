#include <stdio.h>
#include <stdlib.h>
#define MEM_ASSIGN_CHECK(temp) if(temp == NULL){ printf("Heap not Allocated.\n"); return list; }

struct Node{
    int data;
    struct Node *next;
};

// Note: the head will always point to the last node of the cirular linked list.
// because it will reduce the time complexity for adding the element at the begining and end of the list.
// else everything is same as of the standard implementation.

struct Node *addAtBeg(struct Node *, int);
struct Node *addAtEnd(struct Node *, int);
struct Node *addAtPos(struct Node *, int, int);
struct Node *deleteNode(struct Node *, int);
int searchNode(struct Node *, int);
void printList(struct Node *);
struct Node *freeList(struct Node *);

struct Node *addAtBeg(struct Node *list, int data){
    if(list == NULL){
        struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
        MEM_ASSIGN_CHECK(temp)
        temp->data = data;
        temp->next = temp;
        return temp;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->next = list->next;
    list->next = temp;

    return list;
}

struct Node *addAtEnd(struct Node *list, int data){
    if(list == NULL) return addAtBeg(list, data);

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    MEM_ASSIGN_CHECK(temp)
    temp->data = data;
    temp->next = list->next;
    list->next = temp;
    list = temp;

    return list;
}

struct Node *addAtPos(struct Node *list, int data, int pos){
    if(pos < 0) return list;
    if(list == NULL) return addAtBeg(list, data);
    if(pos == 0) return addAtBeg(list, data);
    if(list->next == list) return addAtEnd(list, data);

    struct Node *ptr = list->next;
    int ind = 1;

    while(ptr->next != list->next){
        if(ind == pos){
            struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
            MEM_ASSIGN_CHECK(temp)
            temp->data = data;
            temp->next = ptr->next;
            ptr->next = temp;
            return list;
        }
        
        ptr = ptr->next;
        ind++;
    }
    
    return addAtEnd(list, data);
}

struct Node *deleteNode(struct Node * list, int data){
    if(list == NULL) return list; // if list is empty
    if(list->next == list && list->data == data){ // if list contains only 1 node and that is to be deleted.
        free(list);
        return NULL;
    }

    struct Node *temp;
    if(list->next->data == data){ // if the first node is to be deleted.
        temp = list->next;
        list->next = temp->next;
        free(temp);
        return list;
    }

    struct Node *ptr = list->next;
    while(ptr->next != list){
        if(ptr->next->data == data){
            temp = ptr->next;
            ptr->next = temp->next;
            free(temp);
            return list;
        }

        ptr = ptr->next;
    }

    if(list->data == data){ // to delete the last node
        temp = list;
        ptr->next = temp->next;
        list = ptr;
        free(temp);
    }

    return list;
}

int searchNode(struct Node *list, int data){
    if(list == NULL) return -1;

    // we can also implement the same using 'do while' loop.
    struct Node *ptr = list->next, *head = list;
    int pos = 0;
    while(ptr != head){
        if(ptr->data == data) return pos;
        ptr = ptr->next;
        pos++;
    }

    if(head->data == data) return pos;

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
    if(list == NULL) return NULL;

    struct Node *ptr = list->next, *temp, *head = list;
    while(ptr != head){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    free(ptr);
    return NULL;
}