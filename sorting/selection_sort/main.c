#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp));

void selection_sort(int arr[], int n)
{
    int key, j;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
        {
            arr[j + 1] = arr[j];
        }

        arr[j + 1] = key;
    }
}

int main(void)
{
    int arr[MAX_SIZE];
    int n = MAX_SIZE;

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    puts("");

    selection_sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}