#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType
{
    int v_cnt;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

bool selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 방문되지 않은 것 중 최소 dist 값을 갖는 정점 반환
int get_min_vertex(int n)
{
    int v = -1;
    int min_dist = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (!selected[i] && distance[i] < min_dist)
        {
            v = i;
            min_dist = distance[i];
        }
    }

    return v;
}

void prim(GraphType *g, int from)
{
    for (int u = 0; u < (g->v_cnt); u++)
    {
        distance[u] = INF;
    } distance[from] = 0;

    for (int i = 0; i < (g->v_cnt); i++)
    {
        // distance[u] is the smallest
        int u = get_min_vertex(g->v_cnt);
        if (distance[u] == INF) return;

        selected[u] = true;

        printf("정점 %d 추가, w: %d\n", u, distance[u]);
        for (int v = 0; v < (g->v_cnt); v++)
        {
            if (g->weight[u][v] == INF) continue;

            // get "possible" smallest distance
            if (!selected[v] && g->weight[u][v] < distance[v])
            {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

int main(void)
{
    GraphType g =
    {
        7,

        {
            { 0, 29, INF, INF, INF, 10, INF },
            { 29, 0, 16, INF, INF, INF, 15 },
            { INF, 16, 0, 12, INF, INF, INF },
            { INF, INF, 12, 0, 22, INF, 18 },
            { INF, INF, INF, 22, 0, 27, 25 },
            { 20, INF, INF, INF, 27, 0, INF },
            { INF, 15, INF, 18, 25, INF, 0 }
        }
    };

    prim(&g, 0);
    return 0;
}