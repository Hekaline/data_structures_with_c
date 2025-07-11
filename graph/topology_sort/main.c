#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct GraphNode
{
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType
{
    int v_cnt;
    GraphNode *adj_list[MAX_VERTICES];
} GraphType;

bool is_valid(GraphType *g, int start, int end)
{
    return 0 <= start && start < g->v_cnt &&
        0 <= end && end < g->v_cnt;
}

// 그래프 초기화
void init_graph(GraphType *g)
{
    g->v_cnt = 0;

    for (int v = 0; v < MAX_VERTICES; v++)
    {
        g->adj_list[v] = NULL;
    }
}

// 정점 삽입 연산
void insert_vertex(GraphType *g/*, int v*/)
{
    if (g->v_cnt + 1 > MAX_VERTICES)
    {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }

    g->v_cnt++;
}

// 간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
    if (!is_valid(g, start, end))
    {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }

    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));

    // 간선 역방향 삽입 (head(adj_list[start])가 node가 됨)
    node->vertex = end;
    node->link = g->adj_list[start];
    g->adj_list[start] = node;
}

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct
{
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top = -1;
}

// 공백 상태 검출 함수
bool is_empty(StackType *s)
{
    return s->top == -1;
}

// 포화 상태 검출 함수
bool is_full(StackType *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

// 삽입 함수
void push(StackType *s, element item)
{
    if (is_full(s))
    {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }

    s->stack[++s->top] = item;
}

// 삭제 함수
element pop(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }

    return s->stack[s->top--];
}

// 위상 정렬 수행
bool topology_sort(GraphType *g)
{
    int i;
    int *in_degrees = (int *)calloc(g->v_cnt, g->v_cnt * sizeof(int));

    GraphNode *node;
    for (i = 0; i < g->v_cnt; i++)
    {
        node = g->adj_list[i];

        while (node != NULL)
        {
            in_degrees[node->vertex]++;
            node = node->link;
        }
    }

    // 진입 차수가 0인 정점을 스택에 삽입
    StackType s;
    init_stack(&s);

    for (i = 0; i < g->v_cnt; i++)
    {
        if (in_degrees[i] == 0)
            push(&s, i);
    }

    while (!is_empty(&s))
    {
        element curr = pop(&s);
        node = g->adj_list[curr];

        printf("정점 %d -> ", curr);

        while (node != NULL)
        {
            int next = node->vertex;
            if (--in_degrees[next] == 0)
            {
                push(&s, next);
            }
            node = node->link;
        }
    }

    free(in_degrees);
    printf("\n");

    // 위상 정렬 성공 여부
    return i == g->v_cnt;
}

int main(void)
{
    GraphType g;

    init_graph(&g);

    for (int i = 0; i < 6; i++)
    {
        insert_vertex(&g/*, i*/);
    }

    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);


    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);

    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);

    insert_edge(&g, 3, 5);

    insert_edge(&g, 4, 5);

    topology_sort(&g);

    return 0;
}