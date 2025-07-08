#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct
{
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
bool is_empty(QueueType *q)
{
    return q->front == q->rear;
}

// 포화 상태 검출 함수
bool is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 삽입 함수
void enqueue(QueueType *q, element val)
{
    if (is_full(q))
    {
        error("큐가 포화 상태입니다.");
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = val;
}

// 삭제 함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
    {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

#define MAX_VERTICES 50
typedef struct GraphType
{
    int v_cnt;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

bool visited[MAX_VERTICES];

bool is_valid(GraphType *g, int start, int end)
{
    return 0 <= start && start < g->v_cnt &&
        0 <= end && end < g->v_cnt;
}

void init_graph(GraphType *g)
{
    g->v_cnt = 0;
    for (int r = 0; r < MAX_VERTICES; r++)
    {
        for (int c = 0; c < MAX_VERTICES; c++)
        {
            g->adj_mat[r][c] = false;
        }
    }
}

// 정점 삽입
void insert_vertex(GraphType *g/*, int v <- don't even need it 🥀*/)
{
    if (g->v_cnt + 1 > MAX_VERTICES)
    {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }

    g->v_cnt++;
}

// 간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
    if (!is_valid(g, start, end))
    {
        fprintf(stderr, "그래프: 정점 번호가 유효하지 않음\n");
        return;
    }

    g->adj_mat[start][end] = true;
    g->adj_mat[end][start] = true; // 양방향
}

void bfs_mat(GraphType *g, int from)
{
    QueueType q;
    init_queue(&q);

    enqueue(&q, from);
    visited[from] = true;

    while (!is_empty(&q))
    {
        int curr = dequeue(&q);
        printf("%d -> ", curr);

        for (int next = 0; next < g->v_cnt; next++)
        {
            if (visited[next] || !g->adj_mat[curr][next]) continue;

            visited[next] = true;
            enqueue(&q, next);
        }
    }
}

int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init_graph(g);

    for (int i = 0; i < 6; i++)
        insert_vertex(g);

    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    // printf("\n");
    free(g);
    return 0;
}