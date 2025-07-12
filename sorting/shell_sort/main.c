#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

void inc_insertion_sort(int arr[], int left, int right, int gap)
{
    int j, key;
    for (int i = left + gap; i <= right; i += gap)
    {
        key = arr[i];

        for (j = i - gap; j >= left && arr[j] > key; j -= gap)
        {
            arr[j + gap] = arr[j];
        }

        arr[j + gap] = key;
    }
}

void shell_sort(int arr[], int n)
{
    for (int gap = n / 2; gap >= 1; gap /= 2)
    {
        if (gap % 2 == 0)
            gap++;

        for (int i = 0; i < gap; i++)
        {
            inc_insertion_sort(arr, i, n - 1, gap);
        }
    }
}

int main(void)
{
    int arr[MAX_SIZE];
    int n = MAX_SIZE;

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    shell_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}