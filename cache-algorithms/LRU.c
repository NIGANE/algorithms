#include <stdio.h>
#include <stdlib.h>
#define TOP 5

typedef struct node{
    int key;
    int value;
    struct node* next;
    struct node* prev;
} Node ;

typedef struct {
    int size;
    Node* head;
    Node* tail;
    Node* hashmap[TOP];
} Cache;

void evictTail(Cache* cache);
void moveToHead(Cache* cache, Node* node);

Cache* createCache(){
    Cache* cache = malloc(sizeof(Cache));
    cache->size = 0;
    cache->head = cache->tail = NULL;
    return cache;
}

int getValue(Cache* cache, int key){
    if(cache->hashmap[key]){
        moveToHead(cache, cache->hashmap[key]);
        return cache->hashmap[key]->value;
    }
    return -1;
}

void putValue(Cache* cache, int value){
    Node* node = cache->hashmap[value];
    if(node){
        node->value = value;
        moveToHead(cache, node);
        return;
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = new_node->prev = NULL;
    if(cache->size == TOP){
        evictTail(cache);
    }
    
    //insert at the head
    new_node->next = cache->head;
    if(cache->head) cache->head->prev = new_node;
    cache->head = new_node;
    if(!cache->tail) cache->tail = new_node;
    cache->size++;

}
void moveToHead(Cache* cache, Node* node){
    if(cache->head == node) return;

    if(node->prev) node->prev->next = node->next;
    if(node->next) node->next->prev = node->prev;
    if(node == cache->tail) cache->tail = node->prev;

    node->prev = NULL;
    node->next = cache->head;
    cache->head->prev = node;
    cache->head = node;
}

void evictTail(Cache* cache){
    Node* temp = cache->tail;
    cache->tail = cache->tail->prev;
    cache->tail->next = NULL;
    free(temp);
}

void deleteCache(Cache* cache){

    // free linkedList;
    Node* current = cache->head;
    while(current != NULL){
        Node* temp = current;

        current->prev = NULL;
        current = current->next;
        free(temp);
    }

    // free hashmap;
    for(int i =0; i < TOP; i++){
        cache->hashmap[i] = NULL;
    }
    free(cache);

    // resize the cache size;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
}   

void printCache(Cache* cache){
    int i = 0;
    while(cache->hashmap[i])
    printf(" [%d] ", cache->hashmap[i]->value);
}
void main (){
    
}