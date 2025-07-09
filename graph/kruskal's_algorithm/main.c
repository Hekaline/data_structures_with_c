#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void init_parents(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = i;
}

// curr가 속하는 집합 반환
int find_set(int curr)
{
    if (parent[curr] == curr)
        return curr;

    return parent[curr] = find_set(parent[curr]);
}

// 두 개의 원소가 속한 집합을 합한다.
void set_union(int a, int b)
{
    int root1 = find_set(a);
    int root2 = find_set(b);

    if (root1 == root2) return;

    parent[root2] = root1;
}

struct Edge
{
    int start, end, weight;
};

typedef struct GraphType
{
    int e_cnt;
    int v_cnt;
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화
void init_graph(GraphType *g)
{
    g->v_cnt = g->e_cnt = 0;

    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// 간선 삽입 연산
void insert_edge(GraphType *g, int start, int end, int w)
{
    g->edges[g->e_cnt].start = start;
    g->edges[g->e_cnt].end = end;
    g->edges[g->e_cnt].weight = w;

    g->e_cnt++;
}

// qsort에 사용되는 비교 함수
int compare(const void *a, const void *b)
{
    struct Edge *x = (struct Edge*)a;
    struct Edge *y = (struct Edge*)b;

    return (x->weight - y->weight);
}

// kruskal's algorithm
void kruskal(GraphType *g)
{
    int accepted_edges = 0;
    int u_set, v_set;

    struct Edge e;

    init_parents(g->v_cnt);
    qsort(g->edges, g->e_cnt, sizeof(struct Edge), compare);

    printf("크루스칼 최소 신장 트리 알고리즘\n");
    int i = 0;
    while (accepted_edges < (g->v_cnt - 1))
    {
        e = g->edges[i];
        u_set = find_set(e.start);
        v_set = find_set(e.end);


        if (u_set != v_set)
        {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            accepted_edges++;
            set_union(u_set, v_set);
        }
        i++;
    }
}

int main(void)
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init_graph(g);

    g->v_cnt = 7;
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);

    return 0;
}