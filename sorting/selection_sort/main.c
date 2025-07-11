#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp));

void selection_sort(int list[], int n)
{
    int least, temp;
    for (int i = 0; i < n; i++)
    {
        least = i;
        for (int j = i + 1; j < n; j++)
        {
            if (list[j] < list[least])
                least = j;
        }

        SWAP(list[i], list[least], temp);
    }
}

int main(void)
{
    int arr[MAX_SIZE];
    int n = MAX_SIZE;

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;

    selection_sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}