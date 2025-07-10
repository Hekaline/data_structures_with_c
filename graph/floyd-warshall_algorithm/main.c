#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000000
#define MIN(a, b) (a < b ? a : b)

typedef struct GraphType
{
    int v_cnt;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int dist[MAX_VERTICES][MAX_VERTICES];

void print_dist(GraphType *g)
{
    printf("=============================\n");
    for (int i = 0; i < g->v_cnt; i++)
    {
        for (int j = 0; j < g->v_cnt; j++)
        {
            if (dist[i][j] == INF)
                printf(" * ");
            else
                printf("%3d ", dist[i][j]);
        }

        printf("\n");
    }
    printf("=============================\n");
}

void floyd_warshall(GraphType *g)
{
    for (int i = 0; i < g->v_cnt; i++)
    {
        for (int j = 0; j < g->v_cnt; j++)
        {
            dist[i][j] = g->weight[i][j];
        }
    }
    print_dist(g);

    for (int i = 0; i < g->v_cnt; i++)
    {
        for (int j = 0; j < g->v_cnt; j++)
        {
            for (int k = 0; k < g->v_cnt; k++)
            {
                dist[i][k] = MIN(dist[i][k], dist[i][j] + dist[j][k]);
            }
        }

        print_dist(g);
    }
}

int main(void)
{
    GraphType g =
    {
        7,
        {
            { 0, 7, INF, INF, 3, 10, INF },
            { 7, 0, 4, 10, 2, 6, INF },
            { INF, 4, 0, 2, INF, INF, INF },
            { INF, 10, 2, 0, 11, 9, 4 },
            { 3, 2, INF, 11, 0, INF, 5 },
            { 10, 6, INF, 9, INF, 0, INF },
            { INF, INF, INF, 4, 5, INF, 0 },
        }
    };

    floyd_warshall(&g);
    return 0;
}