#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Queue{
    int *ptr;
    int length;
    int front;
    int rear;
};

struct Result{
    bool success;
    int value;
};

void initQueue(struct Queue *, int *, int);
bool enqueue(struct Queue *, int);
struct Result dequeue(struct Queue *);
struct Result peekFront(struct Queue *);
struct Result peekRear(struct Queue *);
bool isEmpty(struct Queue *);
bool isFull(struct Queue *);
void printQueue(struct Queue *);

void initQueue(struct Queue *qu, int *array, int length){
    qu->ptr = array; // array storing the queue
    qu->length = length; // size of the array
    qu->front = qu->rear = -1; // initially both points to -1
}

bool enqueue(struct Queue *qu, int data){
    if(qu->rear == qu->length-1) return false;
    else if(qu->front == -1 && qu->rear == -1) qu->front = qu->rear = 0;
    else qu->rear++;

    qu->ptr[qu->rear] = data;
    return true;
}

struct Result dequeue(struct Queue *qu){
    struct Result res;

    if(qu->front == -1 && qu->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else if(qu->front == qu->rear){
        res.success = true;
        res.value = qu->ptr[qu->front];
        qu->front = qu->rear = -1;
    }
    else{
        res.success = true;
        res.value = qu->ptr[qu->front];
        qu->front++;
    }

    return res;
}

struct Result peekFront(struct Queue *qu){
    struct Result res;

    if(qu->front == -1 && qu->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = qu->ptr[qu->front];
    }

    return res;
}

struct Result peekRear(struct Queue *qu){
    struct Result res;

    if(qu->front == -1 && qu->rear == -1){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = qu->ptr[qu->rear];
    }

    return res;
}

bool isEmpty(struct Queue *qu){
    return qu->front == -1 && qu->rear == -1;
}

bool isFull(struct Queue *qu){
    return qu->rear == qu->length-1;
}

void printQueue(struct Queue *qu){
    if(qu->front == -1 && qu->rear == -1){
        printf("Queue is empty.\n");
        return;
    }

    for(int i=qu->front; i<=qu->rear; i++) printf("%d ", qu->ptr[i]);
    printf("\n");
}