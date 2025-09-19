#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *next;
};

struct Stack{
    struct Node *top;
};

struct Result{
    bool success;
    int value;
};

void initStack(struct Stack *);
bool push(struct Stack *, int);
struct Result pop(struct Stack *);
struct Result peek(struct Stack *);
bool isEmpty(struct Stack *);
void printStack(struct Stack *);
void freeStack(struct Stack *);

void initStack(struct Stack *st){
    st->top = NULL;
}

bool push(struct Stack *st, int data){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    if(node == NULL){ // if heap is not assigned to the node due to memory issue.
        return false;
    }

    node->data = data;
    node->next = st->top;
    st->top = node;

    return true;
}

struct Result pop(struct Stack *st){
    struct Result res;

    if(st->top == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        struct Node *temp = st->top;
        st->top = st->top->next;
        res.success = true;
        res.value = temp->data;
        free(temp);
    }

    return res;
}

struct Result peek(struct Stack *st){
    struct Result res;

    if(st->top == NULL){
        res.success = false;
        res.value = INT_MAX;
    }
    else{
        res.success = true;
        res.value = st->top->data;
    }

    return res;
}

bool isEmpty(struct Stack *st){    
    return st->top == NULL; // return true if st->top points to any node else return false
}

void printStack(struct Stack *st){
    if(st->top == NULL){
        printf("Stack is empty.\n");
        return;
    }

    struct Node *ptr = st->top;
    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    
    printf("\n");
}

void freeStack(struct Stack *st){
    if(st->top == NULL) return;

    struct Node *ptr = st->top, *temp;
    while(ptr != NULL){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    st->top = NULL;
}