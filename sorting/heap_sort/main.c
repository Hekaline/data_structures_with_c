#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ELEMENT 20

// min heap
int heap[MAX_ELEMENT * 2];
int h_cnt = 0;

void push(int value)
{
    ++h_cnt;

    int parent = h_cnt / 2;
    int child = h_cnt;

    // min heap
    while (parent > 0 && value < heap[parent])
    {
        heap[child] = heap[parent];
        child = parent;
        parent = parent / 2;
    }

    heap[child] = value;
}

int pop()
{
    int ret = heap[1];
    int last = heap[h_cnt--];

    int parent = 1;
    while (parent * 2 <= h_cnt)
    {
        int lchild = parent * 2;
        int rchild = parent * 2 + 1;
        int min_child = lchild;

        if (rchild <= h_cnt && heap[rchild] < heap[lchild])
            min_child = rchild;

        if (heap[min_child] < last)
        {
            heap[parent] = heap[min_child];
            parent = min_child;
        }
        else
            break;
    }

    heap[parent] = last;
    return ret;
}

int main(void)
{
    int arr[MAX_ELEMENT];
    int n = MAX_ELEMENT;

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        push(arr[i]);
        printf("%d ", arr[i]);
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        arr[i] = pop();
        printf("%d ", arr[i]);
    }
}