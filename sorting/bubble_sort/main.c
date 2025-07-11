#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 20
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

void bubble_sort(int arr[], int n)
{
    int temp;

    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
                SWAP(arr[j], arr[j + 1], temp);
        }
    }
}

int main(void)
{
    int arr[MAX_ELEMENT];
    int n = MAX_ELEMENT;

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    bubble_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}