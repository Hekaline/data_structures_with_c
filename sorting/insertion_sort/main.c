#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 20
// #define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

void insertion_sort(int arr[], int n)
{
    int key, j;

    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        for (j = i; j > 0; j--)
        {
            // 이미 정렬됨
            if (arr[j - 1] <= key) break;

            // 오른쪽으로 밀기
            arr[j] = arr[j - 1];
        }

        arr[j] = key;
    }
}

int main(void)
{
    srand(time(NULL));

    int arr[MAX_ELEMENT];
    int n = MAX_ELEMENT;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    insertion_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}