#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100

// BST
// Note: The BST should not contain any duplicate element.
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct BSTree{
    struct Node *head;
};

// STACK
struct Stack{
    struct Node **ptr;
    int top;
    int length;
};

// QUEUE
struct Queue{
    struct Node **ptr;
    int front;
    int rear;
    int length;
};

// STACK FUNCTION PROTOTYPE
void initStack(struct Stack *, struct Node **, int);
bool push(struct Stack *, struct Node *);
struct Node *pop(struct Stack *);
struct Node *peek(struct Stack *);
bool isEmptyStack(struct Stack *);
bool isFullStack(struct Stack *);
int stackSize(struct Stack *);

// QUEUE FUNCTION PROTOTYPE
void initQueue(struct Queue *, struct Node **, int);
bool enqueue(struct Queue *, struct Node *);
struct Node *dequeue(struct Queue *);
struct Node *peekFront(struct Queue *);
struct Node *peekRear(struct Queue *);
bool isEmptyQueue(struct Queue *);
bool isFullQueue(struct Queue *);
int queueSize(struct Queue *);

// STACK CODE
void initStack(struct Stack *st, struct Node **array, int length){
    st->ptr = array;
    st->top = -1;
    st->length = length;
}

bool push(struct Stack *st, struct Node *node){
    if(st->top == st->length-1) return false;
    st->ptr[++st->top] = node;

    return true;
}

struct Node *pop(struct Stack *st){
    if(st->top == -1) return NULL;
    return st->ptr[st->top--];
}

struct Node *peek(struct Stack *st){
    if(st->top == -1) return NULL;
    return st->ptr[st->top];
}

bool isEmptyStack(struct Stack *st){
    return st->top == -1;
}

bool isFullStack(struct Stack *st){
    return st->top == st->length-1;
}

int stackSize(struct Stack *st){
    return st->top + 1;
}

// QUEUE CODE
void initQueue(struct Queue *qu, struct Node **array, int length){
    qu->ptr = array;
    qu->front = qu->rear = -1;
    qu->length = length;
}

bool enqueue(struct Queue *qu, struct Node *node){
    if((qu->rear + 1) % qu->length == qu->front) return false;
    
    if(qu->front == -1) qu->front = 0;
    qu->rear = (qu->rear + 1) % qu->length;
    qu->ptr[qu->rear] = node;
    return true;
}

struct Node *dequeue(struct Queue *qu){
    if(qu->front == -1) return NULL;

    struct Node *temp = qu->ptr[qu->front];
    if(qu->front == qu->rear) qu->front = qu->rear = -1;
    else qu->front = (qu->front + 1) % qu->length;

    return temp;
}

struct Node *peekFront(struct Queue *qu){
    if(qu->front == -1) return NULL;
    return qu->ptr[qu->front];
}

struct Node *peekRear(struct Queue *qu){
    if(qu->front == -1) return NULL;
    return qu->ptr[qu->rear];
}

bool isEmptyQueue(struct Queue *qu){
    return qu->front == -1;
}

bool isFullQueue(struct Queue *qu){
    return (qu->rear + 1) % qu->length == qu->front;
}

int queueSize(struct Queue *qu){
    if(qu->front == -1) return 0;
    return (qu->rear + 1 + qu->length - qu->front) % qu->length; // we modulo by qu->length so that it works when qu->front < qu->rear
}

// BST FUNCTION PROTOTYPE
void initBSTree(struct BSTree *bst);
struct Node *insert(struct BSTree *, int);
struct Node *delete(struct BSTree *, int, char);
struct Node *search(struct BSTree *, int);
int heightQueue(struct BSTree *); // using bfs concept
int heightStack(struct BSTree *); // using dfs concept
void freeBst(struct BSTree *);

// Traversal PROTOTYPE
void preorder(struct BSTree *);
void inorder(struct BSTree *);
void postorder(struct BSTree *);
void bfs(struct BSTree *); // level order traversal

// BST CODE
void initBSTree(struct BSTree *bst){
    bst->head = NULL;
}

struct Node *insert(struct BSTree *bst, int data){
    if(bst == NULL) return NULL; // if bst has not been initialized

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL){
        fprintf(stderr, "Heap memory not allocated!");
        return NULL;
    }
    temp->data = data;
    temp->left = temp->right = NULL;

    if(bst->head == NULL){ // if data is to be inserted at root.
        bst->head = temp;
        return temp;
    } 

    struct Node *ptr = bst->head;
    struct Node *parent = NULL;
    while(ptr != NULL){
        parent = ptr;
        if(data < ptr->data) ptr = ptr->left;
        else if(data > ptr->data) ptr = ptr->right;
        else{ // if data already exists.
            free(temp);
            return bst->head;
        }
    }

    if(data < parent->data) parent->left = temp;
    else parent->right = temp;

    return bst->head;
}

struct Node *delete(struct BSTree *bst, int data, char choice){
    if(bst == NULL || bst->head == NULL) return NULL; // if tree is empty

    struct Node *curr_node = bst->head;
    struct Node *parent = NULL;

    // Searching the node and it's parent
    while(curr_node != NULL && curr_node->data != data){
        parent = curr_node;
        if(data < curr_node->data) curr_node = curr_node->left;
        else curr_node = curr_node->right;
    }

    if(curr_node == NULL) return bst->head; // if either data doesn't exist or bst is empty.

    // CASE-1: No child exists.
    if(curr_node->left == NULL && curr_node->right == NULL){
        if(parent == NULL) bst->head = NULL; // if root is to deleted.
        else if(parent->left == curr_node) parent->left = NULL; // if it's a left child.
        else parent->right = NULL; // if it's a right child.

        free(curr_node);
        return bst->head;;
    }

    // CASE-2: One child exist.
    if(curr_node->left != NULL && curr_node->right == NULL){ // if the node to be deleted has only left child.
        if(parent == NULL) bst->head = curr_node->left; // if root is to be deleted.
        else if(parent->left == curr_node) parent->left = curr_node->left; // if parent's left child is to be deleted.
        else parent->right = curr_node->left; // if parent's right child is to be deleted.

        free(curr_node);
        return bst->head;
    }
    if(curr_node->left == NULL && curr_node->right != NULL){ // if the node to be deleted has only right child.
        if(parent == NULL) bst->head = curr_node->right; // if root is to be deleted.
        else if(parent->left == curr_node) parent->left = curr_node->right; // if parent's left child is to be deleted.
        else parent->right = curr_node->right; // if parent's right child is to be deleted.

        free(curr_node);
        return bst->head;
    }

    // CASE-3: Two child exists.
    if(curr_node->left != NULL && curr_node->right != NULL){
        if(choice == 'p'){ // replacing by inorder predecessor.
            struct Node *predecessor_parent = curr_node;
            struct Node *predecessor = curr_node->left;
            while(predecessor->right != NULL){
                predecessor_parent = predecessor;
                predecessor = predecessor->right;
            }

            curr_node->data = predecessor->data; // copying the data of predecessor to the node to be deleted.

            // attaching the child of the inorder predecessor to it's parent node.
            if(predecessor_parent->left == predecessor) predecessor_parent->left = predecessor->left;
            else predecessor_parent->right = predecessor->left;;

            free(predecessor);
        }
        else{ // default is inorder predecessor.
            // finding the successor and it's parent
            struct Node *successor_parent = curr_node;
            struct Node *successor = curr_node->right;
            while(successor->left != NULL){
                successor_parent = successor;
                successor = successor->left;
            }

            curr_node->data = successor->data; // copying the data of successor to the node to be deleted.

            // attaching the child of the inorder successor to it's parent node.
            if(successor_parent->left == successor) successor_parent->left = successor->right;
            else successor_parent->right = successor->right;

            free(successor);
        }
        return bst->head;
    }

    return bst->head;
}

struct Node *search(struct BSTree *bst, int search_key){
    if(bst == NULL || bst->head == NULL) return NULL;

    struct Node *ptr = bst->head;
    while(ptr != NULL){
        if(search_key < ptr->data) ptr = ptr->left;
        else if(search_key > ptr->data) ptr = ptr->right;
        else return ptr;
    }

    return NULL;
}

int heightQueue(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return 0;

    struct Queue queue1;
    struct Node *array[N];
    struct Node *temp;

    initQueue(&queue1, array, N);
    enqueue(&queue1, bst->head);

    int height = 0;
    int level_order;
    while(!isEmptyQueue(&queue1)){
        level_order = queueSize(&queue1);
        for(int i=0; i<level_order; i++){
            temp = dequeue(&queue1);
            if(temp->left != NULL) enqueue(&queue1, temp->left);
            if(temp->right != NULL) enqueue(&queue1, temp->right);
        }

        height++;
    }

    return height;
}

int heightStack(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return 0;

    struct Node *curr_node = bst->head;
    struct Node *last_visited = NULL;
    struct Node *peek_node = NULL;
    struct Stack stack1;
    struct Node *array[N];

    initStack(&stack1, array, N);

    int curr_height = 0;
    int max_height = 0;
    while(curr_node != NULL || !isEmptyStack(&stack1)){
        if(curr_node != NULL){
            push(&stack1, curr_node);
            curr_height++;
            if(curr_height > max_height) max_height = curr_height;

            curr_node = curr_node->left; // if no left child exist then curr_node = NULL and the backtracking will happen at else part
        }
        else{
            peek_node = peek(&stack1);

            // if right child exits and hasn't been visited
            if(peek_node->right != NULL && last_visited != peek_node->right) curr_node = peek_node->right;
            else{ // finished visiting left and right subtrees
                last_visited = pop(&stack1);
                curr_height--;
            }
        }
    }

    return max_height;
}

void freeBst(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return; // tree is empty.

    struct Node *curr_node = bst->head;
    struct Node *last_visited = NULL;
    struct Node *peek_node = NULL;
    struct Stack stack1;
    struct Node *array[N];

    initStack(&stack1, array, N);
    while(curr_node != NULL || !isEmptyStack(&stack1)){
        if(curr_node != NULL){
            push(&stack1, curr_node);
            curr_node = curr_node->left;
        }
        else{
            peek_node = peek(&stack1);
            if(peek_node->right != NULL && peek_node->right != last_visited) curr_node = peek_node->right;
            else{
                last_visited = pop(&stack1);
                free(last_visited);
            }
        }
    }
    
    bst->head = NULL;
    free(bst);
}

// TRAVERSAL
void preorder(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return; // if tree is empty.

    struct Node *ptr = bst->head;
    struct Stack stack1;
    struct Node *array[N];

    initStack(&stack1, array, N);
    push(&stack1, ptr);

    while(!isEmptyStack(&stack1)){
        ptr = pop(&stack1);

        if(ptr != NULL){
            printf("%d ", ptr->data);
            if(ptr->right != NULL) push(&stack1, ptr->right);
            if(ptr->left != NULL) push(&stack1, ptr->left);
        }
    }

    printf("\n");
}

void inorder(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return; // if tree is empty.

    struct Node *ptr = bst->head;
    struct Stack stack1;
    struct Node *array[N];

    initStack(&stack1, array, N);
    while(ptr != NULL || !isEmptyStack(&stack1)){
        while(ptr != NULL){
            push(&stack1, ptr);
            ptr = ptr->left;
        }

        ptr = pop(&stack1);
        printf("%d ", ptr->data);
        ptr = ptr->right;
    }
    printf("\n");
}

void postorder(struct BSTree *bst){
    if(bst == NULL || bst->head == NULL) return; // if tree is empty.

    struct Node *ptr = bst->head;
    struct Node *last_visited = NULL;
    struct Node *peek_node = NULL;
    struct Stack stack1;
    struct Node *array[N];

    initStack(&stack1, array, N);
    while(ptr != NULL || !isEmptyStack(&stack1)){
        if(ptr != NULL){
            push(&stack1, ptr);
            ptr = ptr->left;
        }
        else{
            peek_node = peek(&stack1);
            if(peek_node->right != NULL && last_visited != peek_node->right) ptr = peek_node->right;
            else{
                last_visited = pop(&stack1);
                printf("%d ", last_visited->data);
            }
        }
    }
    printf("\n");
}

void bfs(struct BSTree *bst){
    struct Queue queue1;
    struct Node *array[N];
    struct Node *temp;

    initQueue(&queue1, array, N);
    enqueue(&queue1, bst->head);

    int level_order = 0;
    while(!isEmptyQueue(&queue1)){
        level_order = queueSize(&queue1);
        for(int i=0; i<level_order; i++){
            temp = dequeue(&queue1);
            printf("%d ", temp->data);
            if(temp->left != NULL) enqueue(&queue1, temp->left);
            if(temp->right != NULL) enqueue(&queue1, temp->right);
        }
    }
    printf("\n");
}