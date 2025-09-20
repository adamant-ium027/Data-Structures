#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct CircularQueue{
    int *ptr;
    int length;
    int front;
    int rear;
};

struct Result{
    bool success;
    int value;
};

void initCircularQueue(struct CircularQueue *, int *, int);
bool enqueue(struct CircularQueue *, int);
struct Result dequeue(struct CircularQueue *);
struct Result peekFront(struct CircularQueue *);
struct Result peekRear(struct CircularQueue *);
bool isEmpty(struct CircularQueue *);
bool isFull(struct CircularQueue *);
void printQueue(struct CircularQueue *);

void initCircularQueue(struct CircularQueue *cq, int *array, int length){
    cq->ptr = array;
    cq->length = length;
    cq->front = cq->rear = -1;
}

bool enqueue(struct CircularQueue *cq, int data){
    if((cq->rear == cq->length-1 && cq->front == 0) || (cq->rear+1 == cq->front)) return false;
    else if(cq->front == -1 && cq->rear == -1) cq->front = cq->rear = 0;
    else if(cq->rear == cq->length-1) cq->rear = 0;
    else cq->rear++;

    cq->ptr[cq->rear] = data;
    return true;
}

struct Result dequeue(struct CircularQueue *cq){
    struct Result res;

    if(cq->front == -1 && cq->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else if(cq->front == cq->rear){
        res.success = true;
        res.value = cq->ptr[cq->front];
        cq->front = cq->rear = -1;
    }
    else{
        res.success = true;
        res.value = cq->ptr[cq->front];
        cq->front = (cq->front + 1) % cq->length;
    }

    return res;
}

struct Result peekFront(struct CircularQueue *cq){
    struct Result res;
    
    if(cq->front == -1 && cq->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = cq->ptr[cq->front];
    }

    return res;
}

struct Result peekRear(struct CircularQueue *cq){
    struct Result res;

    if(cq->front == -1 && cq->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = cq->ptr[cq->rear];
    }

    return res;
}

bool isEmpty(struct CircularQueue *cq){
    return cq->front == -1 && cq->rear == -1;
}

bool isFull(struct CircularQueue *cq){
    return (cq->front == 0 && cq->rear == cq->length-1) || (cq->rear+1 == cq->front);
}

void printQueue(struct CircularQueue *cq){
    if(cq->front == -1 && cq->rear == -1){
        printf("Queue is empty.\n");
    }
    else if(cq->front > cq->rear){
        for(int i=cq->front; i<cq->length; i++) printf("%d ", cq->ptr[i]);
        for(int i=0; i<=cq->rear; i++) printf("%d ", cq->ptr[i]);
    }
    else{
        for(int i=cq->front; i<=cq->rear; i++) printf("%d ", cq->ptr[i]);
    }

    printf("\n");
}