#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType
{
    int v_cnt;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
bool visited[MAX_VERTICES];

// 우선순위 큐를 사용하면 시간복잡도 개선 가능
int choose(int distance[], int n, bool visited[])
{
    int min = INT_MAX;
    int minpos = -1;

    for (int i = 0; i < n; i++)
    {
        if (distance[i] < min && !visited[i])
        {
            min = distance[i];
            minpos = i;
        }
    }

    return minpos;
}

void print_status(GraphType *g)
{
    static int step = 1;
    printf("STEP %d, distance: ", step++);

    for (int i = 0; i < g->v_cnt; i++)
    {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }

    printf("\nvisited: ");
    for (int i = 0; i < g->v_cnt; i++)
    {
        printf("%c ", visited[i] ? 'O' : 'X');
    }
    printf("\n\n");
}

void dijkstra(GraphType *g, int start)
{
    for (int i = 0; i < g->v_cnt; i++)
    {
        distance[i] = g->weight[start][i];
        visited[i] = false;
    }

    visited[start] = true;
    distance[start] = 0;

    for (int i = 0; i < g->v_cnt; i++)
    {
        print_status(g);
        int curr = choose(distance, g->v_cnt, visited);

        visited[curr] = true;
        for (int next = 0; next < g->v_cnt; next++)
        {
            if (visited[next]) continue;

            int possible_weight = distance[curr] + g->weight[curr][next];
            if (possible_weight < distance[next])
            {
                distance[next] = possible_weight;
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
            { 0, 7, INF, INF, 3, 10, INF },
            { 7, 0, 4, 10, 2, 6, INF },
            { INF, 4, 0, 2, INF, INF, INF },
            { INF, 10, 2, 0, 11, 9, 4 },
            { 3, 2, INF, 11, 0, INF, 5 },
            { 10, 6, INF, 9, INF, 0, INF },
            { INF, INF, INF, 4, 5, INF, 0 }
        }
    };

    dijkstra(&g, 0);
    return 0;
}