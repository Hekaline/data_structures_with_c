#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 30

int arr[MAX_ELEMENT];

int recursive_binary_search(int target, int left, int right)
{
    if (left > right)
        return -1;

    int mid = (left + right) / 2;
    printf("인덱스 %d부터 %d까지 탐색 중, mid = %d\n", left, right, mid);


    if (arr[mid] == target)
        return mid;

    // else
    if (arr[mid] < target)
    {
        return recursive_binary_search(target, mid + 1, right);
    } else if (arr[mid] > target)
    {
        return recursive_binary_search(target, left, mid - 1);
    }

    return -1;
}

int iterative_binary_search(int target, int left, int right)
{
    if (left > right) return -1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        printf("인덱스 %d부터 %d까지 탐색 중, mid = %d\n", left, right, mid);

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

int compare(const void *a, const void *b)
{
    int f = *(int *)a;
    int s = *(int *)b;

    return f - s;
}

int main(void)
{
    srand(time(NULL));

    int n = MAX_ELEMENT;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 200;
    }

    int target = arr[rand() % n];
    printf("타겟은 %d\n", target);
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("재귀적인 이분 탐색 시작\n");
    int target_idx = recursive_binary_search(target, 0, n - 1);
    printf("%d\n\n", target_idx);

    printf("반복적인 이분 탐색 시작\n");
    target_idx = iterative_binary_search(target, 0, n - 1);
    printf("%d\n", target_idx);
}