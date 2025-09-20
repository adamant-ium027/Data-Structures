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
    int size = 0;
}

bool enqueue(struct PriorityQueue *pq, int data, int priority){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL) return false; // if heap memory is not allocated.

    temp->data = data;
    temp->priority = priority;
    temp->next = pq->head;
    pq->head = temp;
    pq->size++;

    return true;
}

struct Result dequeue(struct PriorityQueue *pq){
    struct Result res = {false, INT_MAX};

    if(pq->size == 0) return res; // if queue is empty.

    res.success = true;
    int max_priority = maxPriority(pq);
    struct Node *temp;
    if(pq->head->priority == max_priority){ // if first node is to deleted.
        temp = pq->head;
        pq->head = NULL;
        res.value = temp->data;
        free(temp);
        
        return res;
    }

    // for all other cases.
    struct Node *ptr = pq->head;
    while(ptr->next != NULL && ptr->next->priority != max_priority) ptr = ptr->next;

    temp = ptr->next;
    ptr->next = ptr->next->next;
    res.value = temp->data;
    free(temp);

    return res;
}

struct Result peek(struct PriorityQueue *pq){
    struct Result res = {false, INT_MAX};

    if(pq->size == 0) return res; // if queue is empty.

    int max_priority = maxPriority(pq);
    struct Node *ptr = pq->head;
    while(ptr != NULL){
        if(max_priority == ptr->priority){
            res.success = true;
            res.value = ptr->data;
            break;
        }
        ptr = ptr->next;
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

    int max_priority = INT_MAX;
    struct Node *ptr = pq->head;
    while(ptr != NULL){
        if(max_priority < ptr->priority) max_priority = ptr->priority;
        ptr = ptr->next;
    }

    return max_priority;
}

void printPriorityQueue(struct PriorityQueue *pq){
    if(pq->size == 0){
        printf("Queue is empty.\n");
        return;
    }

    struct Node *ptr = pq->head;
    while(ptr != NULL){
        printf("%d -> %d\n", ptr->priority, ptr->data);
        ptr = ptr->next;
    }
}