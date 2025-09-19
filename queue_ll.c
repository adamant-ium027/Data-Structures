#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// no need to check eveytime whether front == NULL && rear == NULL for checking whether the queue is empty or not
// I have written this for ease of understanding.

struct Node{ // to create nodes
    int data;
    struct Node *next;
};

struct Queue{ // to store the front and rear node address
    struct Node *front;
    struct Node *rear;
};

struct Result{ // to store the success of operations
    bool success;
    int value;
};

void initQueue(struct Queue *);
bool enqueue(struct Queue *, int);
struct Result dequeue(struct Queue *);
struct Result peekFront(struct Queue *);
struct Result peekRear(struct Queue *);
bool isEmpty(struct Queue *);
void printQueue(struct Queue *);
void freeQueue(struct Queue *);

void initQueue(struct Queue *qu){
    qu->front = qu->rear = NULL;
}

bool enqueue(struct Queue *qu, int data){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL) return false; // heap memory not allocated.

    temp->data = data;
    temp->next = NULL;

    if(qu->front == NULL && qu->rear == NULL) qu->front = qu->rear = temp;
    else{
        qu->rear->next = temp;
        qu->rear = temp;
    }

    return true;
}

struct Result dequeue(struct Queue *qu){
    struct Result res;

    if(qu->front == NULL && qu->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else if(qu->front == qu->rear){
        res.success = true;
        res.value = qu->front->data;

        struct Node *temp = qu->front;
        qu->front = qu->rear = NULL;
        free(temp);
    }
    else{
        res.success = true;
        res.value = qu->front->data;

        struct Node *temp = qu->front;
        qu->front = qu->front->next;
        free(temp);
    }

    return res;
}

struct Result peekFront(struct Queue *qu){
    struct Result res;

    if(qu->front == NULL && qu->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = qu->front->data;
    }

    return res;
}

struct Result peekRear(struct Queue *qu){
    struct Result res;

    if(qu->front == NULL && qu->rear == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = qu->rear->data;
    }

    return res;
}

bool isEmpty(struct Queue *qu){
    return qu->front == NULL && qu->rear == NULL;
}

void printQueue(struct Queue *qu){
    if(qu->front == NULL && qu->rear == NULL){
        printf("Queue is empty.\n");
        return;
    }

    struct Node *ptr = qu->front;
    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }

    printf("\n");
}

void freeQueue(struct Queue *qu){
    if(qu->front == NULL && qu->rear == NULL) return;

    struct Node *ptr = qu->front, *temp;
    while(ptr != NULL){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    qu->front = qu->rear = NULL;
}