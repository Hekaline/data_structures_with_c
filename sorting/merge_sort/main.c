#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

int sorted[MAX_SIZE];

void merge(int arr[], int left, int right)
{
    int mid = (left + right) / 2;

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            sorted[k++] = arr[i++];
        else
            sorted[k++] = arr[j++];
    }

    if (i > mid)
    {
        while (j <= right)
            sorted[k++] = arr[j++];
    } else
    {
        while (i <= mid)
            sorted[k++] = arr[i++];
    }

    for (k = left; k <= right; k++)
        arr[k] = sorted[k];
}

void merge_sort(int arr[], int left, int right)
{
    if (left >= right) return;

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, right);
}

int main(void)
{
    int n = MAX_SIZE;
    int arr[MAX_SIZE];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    printf("\n");
    merge_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}