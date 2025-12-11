#include <stdio.h>
#include <stdlib.h>

#define EMPTY NULL
#define SIZE 5

typedef struct node
{
    int data;
    struct node *next;

} Node;

Node *table[SIZE];

void init()
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = EMPTY;
    }
}

int hash(int data)
{
    return data % SIZE;
}

int insert(int data)
{
    int index = hash(data);

    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = EMPTY;
    Node *current = table[index];
    if (current == EMPTY)
    {
        table[index] = newNode;
    }
    else
    {
        while (current->next != EMPTY)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    return index;
}

int search(int data)
{
    int index = hash(data);

    Node *current = table[index];

    while (current != EMPTY)
    {
        if (current->data == data)
        {
            printf("key %d fount at index %d \n", data, index);
            return index;
        }
        current = current->next;
    }

    printf("key %d not found\n", data);
    return -1;
}

Node *pop(int data)
{
    int index = hash(data);

    Node *current = table[index];
    Node *prev = NULL;

    while (current != EMPTY)
    {
        if (current->data == data)
        {
            if (prev == NULL)
            {

                table[index] = current->next;
            }
            else
            {

                prev->next = current->next;
            }

            current->next == NULL;
            printf("key %d deleted from index : %d", data, index);
            return current;
        }
        prev = current;
        current = current->next;
    }
    printf("element %d not found!", data);
    return NULL;
}

void free_table()
{
    for (int i = 0; i < SIZE; i++)
    {
        Node *current = table[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < SIZE; i++)
    {

        Node *current = table[i];
        if (current == NULL)
        {
            printf("[%d] => EMPTY", i);
        }
        else
        {
            printf("[%d] => ", i);
            while (current != NULL)
            {
                printf("%d -> ", current->data);
                current = current->next;
            }
            printf("EMPTY");
        }
        printf("\n");
    }
}

int main()
{
    insert(134);
    insert(44);
    insert(12);
    insert(100);
    insert(1);
    print_table();

    search(34);
    search(1);
    free_table();
    return 1;
}