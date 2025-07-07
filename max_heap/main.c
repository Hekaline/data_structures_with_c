#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct
{
    int key;
} element;
typedef struct
{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
    return (HeapType *)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType *h)
{
    h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 힙 h에 item 삽입
void insert(HeapType *h, element item)
{
    int i = ++(h->heap_size);

    // 트리를 거슬러 올라가면서 부모 노드와 비교
    while (i != 1 && item.key > h->heap[i / 2].key)
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

// 삭제 함수
element delete(HeapType *h)
{
    element top = h->heap[1];
    element last_leaf = h->heap[(h->heap_size)--];

    int parent = 1, child = 2;
    while (child <= h->heap_size)
    {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key)
            child++;

        if (last_leaf.key >= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = last_leaf;
    return top;
}

void heap_sort(element a[], int n)
{
    HeapType *h = create();
    init(h);

    for (int i = 0; i < n; i++)
    {
        insert(h, a[i]);
    }
    for (int i = (n - 1); i >= 0; i--)
    {
        a[i] = delete(h);
    }

    free(h);
}

// int main(void)
// {
//     element e1 = { 10 }, e2 = { 5 }, e3 = {30};
//     element e4, e5, e6;
//
//     HeapType *heap = create();
//     init(heap);
//
//     insert(heap, e1);
//     insert(heap, e2);
//     insert(heap, e3);
//
//     e4 = delete(heap);
//     e5 = delete(heap);
//     e6 = delete(heap);
//
//     printf("%d %d %d", e4.key, e5.key, e6.key);
//     free(heap);
//
//     return 0;
// }

#define SIZE 8
int main(void)
{
    element list[SIZE] = { 23, 56, 11, 9, 26, 99, 27, 34 };
    heap_sort(list, SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", list[i].key);
    }

    return 0;
}