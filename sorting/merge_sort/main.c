#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

int sorted[MAX_SIZE];

void merge(int arr[], int left, int right)
{
    int mid = (left + right) / 2;

    int i = left, j = mid + 1, k = left;

    // 왼쪽 부분배열과 오른쪽 부분배열 비교
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            sorted[k++] = arr[i++];
        else
            sorted[k++] = arr[j++];
    }

    // 두 부분배열 중 한 쪽이 남았을 경우 전부 옮기기
    if (i > mid)
    {
        while (j <= right)
            sorted[k++] = arr[j++];
    } else
    {
        while (i <= mid)
            sorted[k++] = arr[i++];
    }

    // 임시 배열을 원래 배열에 복사하기
    for (k = left; k <= right; k++)
        arr[k] = sorted[k];
}

void merge_sort(int arr[], int left, int right)
{
    // 크기가 2 이상일 경우 좌우 부분배열로 나눠 비교
    if (left >= right) return;

    // left와 right 차이가 1인 상태에서부터 비교가 시작된다 (크기가 1인 두 부분배열 비교)
    // 그 후 크기가 더 큰 부분배열끼리 비교 -> 더 큰 부분배열 -> ...
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