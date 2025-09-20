#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Note: lower the priority value -> higher the priority.

struct Node{
    int data;
    int priority;
    struct Node *next;
};

struct PriorityQueue{
    struct Node *head;
    int size;
};

struct Result{
    bool success;
    int value;
};

void initPriorityQueue(struct PriorityQueue *);
bool enqueue(struct PriorityQueue *, int, int);
struct Result dequeue(struct PriorityQueue *);
struct Result peek(struct PriorityQueue *);
bool isEmpty(struct PriorityQueue *);
int getSize(struct PriorityQueue *);
int maxPriority(struct PriorityQueue *);
void printPriorityQueue(struct PriorityQueue *);

void initPriorityQueue(struct PriorityQueue *pq){
    pq->head = NULL;
    pq->size = 0;
}

bool enqueue(struct PriorityQueue *pq, int data, int priority){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL) return false; // Heap memory not allocated.

    pq->size++;

    if(pq->size == 0){ // if initially there is no element in the queue.
        temp->data = data;
        temp->priority = priority;
        temp->next = NULL;
        pq->head = temp;
        return true;
    }
    
    if(priority < pq->head->priority){ // if the node is to be inserted as the first node.
        temp->data = data;
        temp->priority = priority;
        temp->next = pq->head;
        pq->head = temp;
        return true;
    }

    // for all other cases
    struct Node *ptr = pq->head;
    while(ptr->next != NULL && priority <= ptr->next->priority) ptr = ptr->next;

    temp->data = data;
    temp->priority = priority;
    temp->next = ptr->next;
    ptr->next = temp;

    return true;
}

struct Result dequeue(struct PriorityQueue *pq){
    struct Result res;

    if(pq->size == 0){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = pq->head->data;

        struct Node *temp = pq->head;
        pq->head = pq->head->next;
        free(temp);
        
        pq->size--;
    }

    return res;
}

struct Result peek(struct PriorityQueue *pq){
    struct Result res;

    if(pq->size == 0){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = pq->head->data;
    }

    return res;
}

bool isEmpty(struct PriorityQueue *pq){
    return pq->size == 0;
}

int getSize(struct PriorityQueue *pq){
    return pq->size;
}

int maxPriority(struct PriorityQueue *pq){
    if(pq->size == 0) return -1; // if queue is empty.

    return pq->head->priority;
}

void printPriorityQueue(struct PriorityQueue *pq){
    if(pq->head == NULL){
        printf("Queue is empty.\n");
        return;
    }

    struct Node *ptr = pq->head;
    while(ptr != NULL){
        printf("%d -> %d\n", ptr->priority, ptr->data);
        ptr = ptr->next;
    }
}