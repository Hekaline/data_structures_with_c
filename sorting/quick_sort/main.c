#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int partition(int arr[], int left, int right)
{
    int temp;

    int low = left;
    int high = right + 1;

    // 두 배열(왼쪽에 더 작은 배열, 오른쪽에 더 큰 배열)을 가르는 기준
    int pivot = arr[left];

    do
    {
        // low가 왼쪽에서부터 출발, high보다 왼쪽에 있으면서 arr[low]가 pivot 및 arr[high]보다 큰 상태가 된다
        do low++; while (arr[low] < pivot);

        // high가 오른쪽에서부터 출발, low보다 오른쪽에 있으면서 arr[high]가 pivot 및 arr[low]보다 작다
        do high--; while (arr[high] > pivot);

        // 밑의 while 문 검사 전이므로 low와 high가 엇갈린 상태일 수 있다
        if (low < high) SWAP(arr[low], arr[high], temp);
    } while (low < high);

    // arr[left] = pivot, 피벗이 이제 가운데(왼쪽 값들보다 크고 오른쪽 값들보다 작은 곳)에 위치한다.
    SWAP(arr[left], arr[high], temp);
    return high;
}

void quick_sort(int arr[], int left, int right)
{
    if (left >= right) return;

    // 배열의 왼쪽은 arr[mid]보다 작고, 오른쪽은 arr[mid]보다 크다
    int mid = partition(arr, left, right);

    // merge와 달리 큰 것에서부터 정렬
    quick_sort(arr, left, mid - 1);
    quick_sort(arr, mid + 1, right);
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

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}