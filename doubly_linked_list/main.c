#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode
{
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

// 이중 연결 리스트 초기화
void init(DListNode *p_head)
{
    p_head->llink = p_head;
    p_head->rlink = p_head;
}

// 이중 연결 리스트의 노드 출력
void print_dlist(DListNode *p_head)
{
    printf("<- head ->");
    for (DListNode *it = p_head->rlink; it != p_head; it = it->rlink)
    {
        printf("<- %d -> ", it->data);
    }
    printf("\n");
}

// 새로운 데이터를 노드 prev의 오른쪽에 삽입
void d_insert(DListNode *prev, element data)
{
    DListNode *new_node = (DListNode *)malloc(sizeof(DListNode));

    new_node->data = data;
    new_node->llink = prev;
    new_node->rlink = prev->rlink;

    // prev의 다음 것이었던 노드의 llink를 new_node로 바꿈
    prev->rlink->llink = new_node;
    prev->rlink = new_node;
}

// 노드 target 제거
void delete(DListNode *head, DListNode *target)
{
    if (head == target) return;

    target->llink->rlink = target->rlink;
    target->rlink->llink = target->llink;
    free(target);
}

int main(void)
{
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));
    init(head);

    printf("추가 단계\n");
    for (int i = 0; i < 5; i++)
    {
        // 헤드 노드 오른쪽에 삽입
        d_insert(head, i);
        print_dlist(head);
    }

    printf("삭제 단계\n");
    for (int i = 0; i < 5; i++)
    {
        print_dlist(head);
        delete(head, head->rlink);
    }

    free(head);
    return 0;
}