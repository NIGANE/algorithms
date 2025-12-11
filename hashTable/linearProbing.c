#include <stdio.h>

#define SIZE 10
#define EMPTY -1
#define DELETE -2

int table[SIZE];

void init()
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = EMPTY;
    }
}

int hash(int key)
{
    return key % SIZE;
}

int insert(int key)
{
    int index = hash(key);
    int origin = index;

    while (table[index] != EMPTY)
    {
        index = (index + 1) % SIZE;
        if (index == origin)
        {
            printf("the table is FULL, cannot insert %d\n", key);
            return -1;
        }
    }

    table[index] = key;
    return index;
}

int search(int key)
{
    int index = hash(key);
    int origin = index;

    while (table[index] != EMPTY)
    {
        if (table[index] == key)
        {
            printf("Key %d Found at index %d\n", key, index);
            return index;
        }
        index = (index + 1) % SIZE;
        if (index == origin || index == DELETE)
        {
            break;
        }
    }
    printf("key %d Not Found\n", key);
    return -1;
}
void delete(int key)
{
    int index = search(key);
    if (index != -1)
    {
        table[index] = DELETE;
        printf("item %d was Deleted from index %d\n", key, index);
    }
    else
    {
        printf("key %d not found \n", key);
    }
}
void print()
{
    printf("==> Hash Table:\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (table[i] == EMPTY)
            printf(" - EMPTY\n");
        else if (table[i] == DELETE)
            printf(" - DELETED\n");
        else
            printf(" - [%d] -> %d\n", i, table[i]);
    }
}

int main()
{
    init();
    insert(12);
    insert(11);
    insert(15);
    insert(113);
    insert(50);
    insert(12);
    print();
}

// this method check if the current index avalaible to hold the data 
// if not it moves by one step ahead 