#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the node structure
typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

// Define the deque structure
typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;

// Function to create a new node
Node* newNode(void* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

// Function to create an empty deque
Deque* createDeque() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = deque->rear = NULL;
    return deque;
}

// Function to add an element at the rear of the deque
void addLast(Deque* deque, void* data) {
    Node* node = newNode(data);

    if (deque->rear == NULL) {
        deque->front = deque->rear = node;
        return;
    }

    deque->rear->next = node;
    node->prev = deque->rear;
    deque->rear = node;
}

// Function to remove an element from the front of the deque
void* removeFirst(Deque* deque) {
    if (deque->front == NULL)
        return NULL;

    Node* temp = deque->front;
    void* data = temp->data;

    deque->front = deque->front->next;
    if (deque->front == NULL)
        deque->rear = NULL;
    else
        deque->front->prev = NULL;

    free(temp);

    return data;
}

// Function to check if the deque is empty
int isEmpty(Deque* deque) {
    return deque->front == NULL;
}