#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int weight;
} Item;

int compare(const void *a, const void *b)
{
    double r1 = (double)((Item *)a)->value / ((Item *)a)->weight;
    double r2 = (double)((Item *)b)->value / ((Item *)b)->weight;
    return r2 > r1 ? 1 : -1;
}

double fractionalKnapsack(Item items[], int n, int capacity)
{
    qsort(items, n, sizeof(Item), compare);

    double totalValue = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (capacity >= items[i].weight)
        {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        else
        {
            totalValue += (double)items[i].value * capacity / items[i].weight;
            break;
        }
    }
    return totalValue;
}

int main()
{
    Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    double maxValue = fractionalKnapsack(items, n, capacity);
    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}
