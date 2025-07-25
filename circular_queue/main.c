#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

// impossible; const's not set in "real" compile time (can be possible with "constexpr" in C++)
// int const MAX_QUEUE_SIZE = 5;

typedef int element;

typedef struct
{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 큐 초기화 함수
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출
_Bool is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출
_Bool is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

// 원형 큐 출력 함수
void print_queue(QueueType* q)
{
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (is_empty(q))
        return;

    int i = q->front;
    do
    {
        i = (i + 1) % MAX_QUEUE_SIZE;
        printf("%d | ", q->data[i]);

        if (i == q->rear)
            break;
    } while (i != q->front);

    printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
    {
        error("큐가 포화 상태입니다.");
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
    if (is_empty(q))
    {
        error("큐가 비어 있습니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 맨 앞의 element 보기 (pop X)
element peek(QueueType* q)
{
    if (is_empty(q))
    {
        error("큐가 비어 있습니다.");
    }

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
    QueueType queue;
    int _element;

    init_queue(&queue);

    printf("-- 데이터 추가 단계 ==\n");
    while (!is_full(&queue))
    {
        printf("정수를 입력하세요: ");
        scanf("%d", &_element);
        enqueue(&queue, _element);
        print_queue(&queue);
    }
    printf("이제 큐가 포화 상태입니다.\n\n");

    printf("-- 데이터 삭제 단계 --\n");
    while (!is_empty(&queue))
    {
        _element = dequeue(&queue);
        printf("꺼낸 정수: %d\n", _element);
        print_queue(&queue);
    }
    printf("이제 큐가 공백 상태입니다.\n");

    return 0;
}