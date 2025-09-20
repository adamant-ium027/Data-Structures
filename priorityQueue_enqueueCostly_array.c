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

    int i;
    for(i=pq->size; i>=0; i--){
        if(pq->ptr[i].priority <= priority){
            pq->ptr[i+1] = pq->ptr[i];
            continue;
        }
        break;
    }

    pq->ptr[i+1] = (struct Element){data, priority};
    pq->size++;

    return true;
}

struct Result dequeue(struct PriorityQueue *pq){
    struct Result res;

    if(pq->size == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = pq->ptr[pq->size].data;
        pq->size--;
    }

    return res;
}

struct Result peek(struct PriorityQueue *pq){
    struct Result res;

    if(pq->size == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = pq->ptr[pq->size].data;
    }

    return res;
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

    return pq->ptr[pq->size].priority;
}

void printPriorityQueue(struct PriorityQueue *pq){
    if(pq->size == -1){
        printf("Queue is empty.\n");
        return;
    }

    for(int i=pq->size; i>=0; i--) printf("%d -> %d\n", pq->ptr[i].priority, pq->ptr[i].data);
}