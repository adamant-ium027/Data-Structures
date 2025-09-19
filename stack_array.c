#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Stack{
    int *ptr; // pointer to the external array
    int length; // total size of the external array
    int top; // index of the top element in the stack
};

struct Result{
    bool success; // stores the success value of different operations
    int value; // stores the value that operation returns and if success = false then it contains INT_MAX.
};

void initStack(struct Stack *, int *, int);
bool push(struct Stack *, int);
struct Result pop(struct Stack *);
struct Result peek(struct Stack *);
bool isEmpty(struct Stack *);
bool isFull(struct Stack *);
void printStack(struct Stack *);

// initialization of array
void initStack(struct Stack *st, int *array, int length){
    st->ptr = array;
    st->length = length;
    st->top = -1;
}

bool push(struct Stack *st, int data){
    if(st->top == st->length-1) return false; // if stack is full

    st->ptr[++st->top] = data; // if stack has atleast 1 index empty

    return true;
}

struct Result pop(struct Stack *st){
    struct Result res;

    if(st->top == -1){ // if stack is empty
        res.success = false;
        res.value = INT_MAX;
    }
    else{ // if stack has atleast 1 element.
        res.success = true;
        res.value = st->ptr[st->top--];
    }

    return res;
}

struct Result peek(struct Stack *st){
    struct Result res;

    if(st->top == -1){ // if stack is empty
        res.success = false;
        res.value = INT_MAX;
    }
    else{ // if stack has atleast 1 element.
        res.success = true;
        res.value = st->ptr[st->top];
    }

    return res;
}

bool isEmpty(struct Stack *st){
    return st->top == -1; // if empty then return true else false
}

bool isFull(struct Stack *st){
    return st->top == st->length-1; // if full then return true else false
}

void printStack(struct Stack *st){ // prints the stack
    if(st->top == -1){
        printf("Stack is empty.\n");
        return;
    }

    for(int i=0; i<=st->top; i++) printf("%d ", st->ptr[i]);
    printf("\n");
}