#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INDEX_SIZE 30
typedef struct
{
    int key;
    int index;
} itable;

int itable_size = 0;
itable itable_arr[INDEX_SIZE];
int arr[INDEX_SIZE];

int seq_search(int key, int low, int high)
{
    for (int i = low; i <= high; i++)
    {
        if (arr[i] == key)
            return i;
    }

    return -1;
}

int search_index(int key, int n)
{
    if (key < arr[0] || key > arr[n - 1])
        return -1;

    int i;
    for (i = 0; i < INDEX_SIZE; i++)
    {
        if (itable_arr[i].key <= key && key <= itable_arr[i + 1].key)
        {
            break;
        }
    }

    int low, high; // 가능한 가장 작은 인덱스와 큰 인덱스
    if (i == INDEX_SIZE)
    {
        low = itable_arr[INDEX_SIZE - 1].index;
        high = n;
    } else
    {
        low = itable_arr[i].index;
        high = itable_arr[i + 1].index;
    }

    return seq_search(key, low, high);
}

int compare(const void *a, const void *b)
{
    int A = *(int *)a;
    int B = *(int *)b;

    return A - B;
}

int main(void)
{
    srand(time(NULL));

    int n = INDEX_SIZE;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    qsort(arr, n, sizeof(int), compare);
    int rand_idx = rand() % n;

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);

        if (i % 3 == 0)
        {
            itable_arr[itable_size].index = i;
            itable_arr[itable_size].key = arr[i];
            itable_size++;
        }
    }

    printf("\n찾으려고 하는 값: %d\n", arr[rand_idx]);
    printf("rand_idx: %d, 함수에서 찾은 위치: %d\n", rand_idx, search_index(arr[rand_idx], n));
}