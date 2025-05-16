#include <stdio.h>
#include <stdlib.h>

#define TOP 4

typedef struct node{
    int data;
    struct node* next;
} Node;

typedef struct queue{
    Node* front;
    Node* rear;
    int size;
} Queue;

void initQueue(Queue* q){
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}
int isPresent(Queue* q, int data){
    Node* current = q->front;
    while(current != NULL){
        if(current->data == data) return 1;
        current = current->next;
    }
    return 0;
}
void dequeue(Queue* q){
    if(q->rear == NULL) return;
    Node* temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->size--;
    if(q->front == NULL) q->rear = NULL;
    return;
}


void enqueue(Queue* q, int data){
    if(isPresent(q, data)){
        return;
    }
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if(q->rear == NULL){
        q->front = newNode;
        q->rear = newNode;
        q->size++;
        return;
    }else if(q->size == TOP){
        dequeue(q);
        enqueue(q, data);
    }else{

        q->rear->next = newNode;
        q->rear = newNode;
        q->size++;
    }

}
void freeing(Queue* q){
   
    if(q->rear == NULL) return;

    Node* cur = q->front;
    while(cur != NULL){
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void printQueue(Queue* q){
    
    if(q->rear == NULL) printf("queue is empty");
    
    Node* current = q->front;
    while(current != NULL){
        if(current != q->front){
            printf("->");
        }
        printf("[%d]", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    int arr[] = {2, 3, 4, 1, 8 , 9};
    Queue* q = malloc(sizeof(Queue));
    initQueue(q);
    // enqueue(q, arr[0]);
    // enqueue(q, arr[1]);
    // enqueue(q, arr[2]);
    // enqueue(q, arr[3]);
    // printQueue(q);

    // enqueue(q, arr[4]);
    // enqueue(q, arr[5]);

    printQueue(q);
    free(q);
}