#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *next;
};

struct CircularQueue{
    struct Node *front;
    struct Node *rear;
};

struct Result{
    bool success;
    int value;
};

void initCircularQueue(struct CircularQueue *);
bool enqueue(struct CircularQueue *, int);
struct Result dequeue(struct CircularQueue *);
struct Result peekFront(struct CircularQueue *);
struct Result peekRear(struct CircularQueue *);
bool isEmpty(struct CircularQueue *);
void printQueue(struct CircularQueue *);
void freeQueue(struct CircularQueue *);

void initCircularQueue(struct CircularQueue *cq){
    cq->front = NULL;
    cq->rear = NULL;
}

bool enqueue(struct CircularQueue *cq, int data){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL) return false; // heap memory not assigned.

    if(cq->front == NULL && cq->rear == NULL){
        temp->data = data;
        temp->next = temp;
        cq->front = cq->rear = temp;
    }
    else{
        temp->data = data;
        temp->next = cq->front;
        cq->rear->next = temp;
        cq->rear = temp;
    }

    return true;
}

struct Result dequeue(struct CircularQueue *cq){
    struct Result res;

    struct Node *temp;
    if(cq->front == NULL && cq->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else if(cq->front == cq->rear){
        res.success = true;
        res.value = cq->front->data;
        temp = cq->front;
        free(temp);
        cq->front = cq->rear = NULL;
    }
    else{
        res.success = true;
        res.value = cq->front->data;
        temp = cq->front;
        cq->front = temp->next;
        cq->rear->next = cq->front;
        free(temp);
    }

    return res;
}

struct Result peekFront(struct CircularQueue *cq){
    struct Result res;

    if(cq->front == NULL && cq->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = cq->front->data;
    }

    return res;
}

struct Result peekRear(struct CircularQueue *cq){
    struct Result res;

    if(cq->front == NULL && cq->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = cq->rear->data;
    }

    return res;
}

bool isEmpty(struct CircularQueue *cq){
    return cq->front == NULL && cq->rear == NULL;
}

void printQueue(struct CircularQueue *cq){
    if(cq->front == NULL && cq->rear == NULL){
        printf("Queue is empty.\n");
        return;
    }

    struct Node *ptr = cq->front;
    do{
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }while(ptr != cq->front);

    printf("\n");
}

void freeQueue(struct CircularQueue *cq){
    if(cq->front == NULL && cq->rear == NULL) return;

    struct Node *ptr = cq->front, *temp;
    do{
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }while(ptr != cq->front);

    cq->front = cq->rear = NULL;
}