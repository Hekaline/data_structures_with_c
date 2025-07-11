#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 50

typedef struct LinkedList
{
    int val;
    struct LinkedList *link;
} LinkedList;

typedef struct GraphType
{
    int v_cnt;
    LinkedList *adj_list[MAX_VERTICES];
} GraphType;

bool visited[MAX_VERTICES];

bool is_valid(const GraphType *const g, int start, int end)
{
    return 0 <= start && start < (g->v_cnt) &&
        0 <= end && end < (g->v_cnt);
}

// 그래프 초기화
void init(GraphType *g)
{
    g->v_cnt = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        g->adj_list[i] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType *g/*, int v*/)
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
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }

    LinkedList *new_node = (LinkedList *)malloc(sizeof(LinkedList));
    new_node->link = g->adj_list[start];
    new_node->val = end;

    g->adj_list[start] = new_node;
}

// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType *g, int v)
{
    visited[v] = true;
    printf("%d -> ", v);

    for (LinkedList *curr_link = g->adj_list[v]; curr_link; curr_link = curr_link->link)
    {
        int w = curr_link->val;
        if (!visited[w])
        {
            dfs_mat(g, w);
        }
    }
}

void reset_visited()
{
    for (int i = 0; i < MAX_VERTICES; i++)
        visited[i] = false;
}

int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 4; i++)
        insert_vertex(g/*, i*/);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("깊이 우선 탐색 (DFS)\n");
    dfs_mat(g, 0);
    // reset_visited();
    // printf("\n");
    // dfs_mat(g, 1);

    free(g);
    return 0;
}