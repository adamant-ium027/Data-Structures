#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Note: lower the priority value -> higher the priority.

struct Element{
    int data;
    int priority;
};

struct PriorityQueue{
    struct Element *ptr;
    int size;
    int length;
};

struct Result{
    bool success;
    int value;
};

void initPriorityQueue(struct PriorityQueue *, struct Element *, int);
bool enqueue(struct PriorityQueue *, int, int);
struct Result dequeue(struct PriorityQueue *);
struct Result peek(struct PriorityQueue *);
bool isEmpty(struct PriorityQueue *);
bool isFull(struct PriorityQueue *);
int getSize(struct PriorityQueue *);
int maxPriority(struct PriorityQueue *);
void printPriorityQueue(struct PriorityQueue *);

void initPriorityQueue(struct PriorityQueue *pq, struct Element *array, int length){
    pq->ptr = array;
    pq->size = -1;
    pq->length = length;
}

bool enqueue(struct PriorityQueue *pq, int data, int priority){
    if(pq->size == pq->length-1) return false;

    pq->ptr[++pq->size] = (struct Element){data, priority};
    return true;
}

struct Result dequeue(struct PriorityQueue *pq){
    struct Result res = {false, INT_MAX};

    if(pq->size == -1) return res;
    
    int max_priority = maxPriority(pq);
    res.success = true;
    
    int i;
    for(i=0; i<=pq->size; i++){ // copying the lowest priority elment
        if(pq->ptr[i].priority == max_priority){
            res.value = pq->ptr[i].data;
            break;
        }
    }

    for(; i<pq->size; i++){ // deleting the lowest priority element
        pq->ptr[i] = pq->ptr[i+1];
    }

    pq->size--; // decreasing the size of the original array

    return res;
}

struct Result peek(struct PriorityQueue *pq){
    struct Result res;

    if(pq->size == -1){
        res.success = false;
        res.value = INT_MAX;
    }

    res.success = true;
    int max_priority = maxPriority(pq);
    for(int i=0; i<=pq->size; i++){
        if(pq->ptr[i].priority == max_priority){
            res.value = pq->ptr[i].data;
            return res;
        }
    }

    return (struct Result){false, INT_MAX};
}

bool isEmpty(struct PriorityQueue *pq){
    return pq->size == -1;
}

bool isFull(struct PriorityQueue *pq){
    return pq->size == pq->length-1;
}

int getSize(struct PriorityQueue *pq){
    return pq->size+1;
}

int maxPriority(struct PriorityQueue *pq){
    if(pq->size == -1) return -1; // if queue is empty.

    int max_priority = INT_MAX; // finding the current max priority in the queue.
    for(int i=0; i<=pq->size; i++){
        if(pq->ptr[i].priority < max_priority) max_priority = pq->ptr[i].priority;
    }

    return max_priority;
}

void printPriorityQueue(struct PriorityQueue *pq){
    if(pq->size == -1){
        printf("Queue is empty.\n");
        return;
    }

    for(int i=pq->size; i>=0; i--) printf("%d -> %d\n", pq->ptr[i].priority, pq->ptr[i].data);
}