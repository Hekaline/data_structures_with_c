#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 30

int arr[MAX_ELEMENT];

int compare(const void *a, const void *b)
{
    int A = *(int *)a;
    int B = *(int *)b;

    return A - B;
}

int interpolation_search(int key, int n)
{
    int low = 0;
    int high = n - 1;

    while (arr[low] < key && key <= arr[high])
    {
        int expect = ((float)(key - arr[low]) / (arr[high] - arr[low]) * (high - low)) + low;
        if (key > arr[expect])
            low = expect + 1;
        else if (key < arr[expect])
            high = expect - 1;
        else
            low = expect;
    }

    if (arr[low] == key) return low;
    return -1;
}

int main(void)
{
    int n = MAX_ELEMENT;
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    qsort(arr, n, sizeof(int), compare);

    int rand_idx = rand() % n;
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n찾을 값: %d, 찾을 인덱스: %d\n", arr[rand_idx], rand_idx);
    printf("보간 탐색해서 찾은 인덱스: %d\n", interpolation_search(arr[rand_idx], n));
}