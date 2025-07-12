#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct
{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message)
{
    fprintf(stderr, "%s", message);
    exit(1);
}

void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

bool is_empty(QueueType *q)
{
    return q->front == q->rear;
}

bool is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("큐가 포화 상태입니다.");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("큐가 공백 상태입니다.");

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

#define BUCKETS 10
#define DIGITS 4
void radix_sort(int arr[], int n)
{
    QueueType queues[BUCKETS];

    for (int b = 0; b < BUCKETS; b++)
        init_queue(&queues[b]);

    // factor는 자릿수 (10^d)
    int i = 0, factor = 1;
    for (int d = 0; d < DIGITS; d++)
    {
        for (i = 0; i < n; i++)
        {
            // factor의 자릿수 (factor가 10이고 arr[i]가 123이면 place_value = 2)
            int place_value = (arr[i] / factor) % 10;
            enqueue(&queues[place_value], arr[i]);
        }

        for (int b = i = 0; b < BUCKETS; b++)
        {
            while (!is_empty(&queues[b]))
            {
                arr[i++] = dequeue(&queues[b]);
            }
        }

        factor *= 10;
    }
}

#define MAX_ELEMENT 40

int main(void)
{
    int arr[MAX_ELEMENT];
    int n = MAX_ELEMENT;
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    printf("\n");
    radix_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}