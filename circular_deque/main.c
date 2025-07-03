#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct
{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} DequeType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화
void init_deque(DequeType *q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
_Bool is_empty(DequeType *q)
{
    return q->front == q->rear;
}

// 포화 상태 검출 함수
_Bool is_full(DequeType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 원형 덱 출력 함수
void print_deque(DequeType *q)
{
    printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
    if (is_empty(q)) return;

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

// 뒤쪽 삽입 함수
void add_rear(DequeType *q, element item)
{
    if (is_full(q))
    {
        error("덱이 포화 상태입니다.");
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 앞쪽 삭제 함수
element delete_front(DequeType *q)
{
    if (is_empty(q))
    {
        error("덱이 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 앞쪽 확인 함수
element get_front(DequeType *q)
{
    if (is_empty(q))
    {
        error("덱이 공백 상태입니다.");
    }

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// 앞쪽 삽입 함수
void add_front(DequeType *q, element item)
{
    if (is_full(q))
    {
        error("덱이 포화 상태입니다.");
    }

    q->data[q->front] = item;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

// 뒤쪽 삭제 함수
element delete_rear(DequeType *q)
{
    if (is_empty(q))
    {
        error("덱이 공백 상태입니다.");
    }

    int prev = q->rear;
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

// 뒤쪽 확인 함수
element get_rear(DequeType *q)
{
    if (is_empty(q))
    {
        error("덱이 공백 상태입니다.");
    }

    return q->data[q->rear];
}

int main(void)
{
    DequeType queue;

    init_deque(&queue);
    for (int i = 0; i < 3; i++)
    {
        add_front(&queue, i);
        print_deque(&queue);
    }

    for (int i = 0; i < 3; i++)
    {
        delete_rear(&queue);
        print_deque(&queue);
    }

    return 0;
}