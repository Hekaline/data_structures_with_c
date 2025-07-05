#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct
{
    element data;
    struct ListNode *link;
} ListNode;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// value를 가지는 새 노드를 head로 만들기
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = value;
    new_node->link = /*(struct ListNode*)*/head;

    head = new_node;
    return head;
}

// 노드 pre 뒤에 새 노드 삽입
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = value;
    new_node->link = pre->link;
    pre->link = new_node;

    return head;
}

ListNode *delete_first(ListNode *head)
{
    if (head == NULL) return NULL;

    ListNode* to_remove = head;
    head = head->link;

    free(to_remove);
    return head;
}

// pre가 가리키는 노드의 다음 노드 삭제
ListNode *delete(ListNode *head, ListNode *pre)
{
    ListNode *to_remove = pre->link;
    pre->link = to_remove->link;
    free(to_remove);

    return head;
}

void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
    {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

element get_entry(ListNode *head, int index)
{
    if (head == NULL)
    {
        error("리스트가 비었습니다");
    }

    if (index < 0)
    {
        error("인덱스가 0보다 작습니다.");
    }

    ListNode *target = head;
    for (int i = 0; i < index; i++)
    {
        target = target->link;
        if (target == NULL)
        {
            error("인덱스가 범위를 초과하였습니다");
        }
    }

    return target->data;
}

ListNode* concat_list(ListNode *head1, ListNode *head2)
{
    if (head1 == NULL)
        return head2;

    if (head2 == NULL)
        return head1;

    ListNode *p;
    p = head1;

    while (p->link != NULL)
    {
        p = p->link;
    }

    p->link = head2;
    return head1;
}

ListNode* reverse_list(ListNode *head)
{
    ListNode *next, *target, *prev;

    next = head; // 맨 앞쪽 노드, target->link 변경 전 "원래" 앞 노드 저장 및 NULL 체크
    target = NULL; // 현재 타깃

    while (next != NULL)
    {
        // 전체적으로 뒤쪽에 가까운 노드 순으로 앞으로 민다

        prev = target; // 뒤 노드를 끌고 옴
        target = next; // 타깃도 앞으로
        next = next->link; // 다음 노드를 앞으로 보낸다

        target->link = prev; // 현 타깃의 링크를 뒤쪽에 연결
    }

    return target;
}

int main(void)
{
    ListNode *head = NULL;

    for (int i = 0; i < 5; i++)
    {
        head = insert_first(head, i);
        print_list(head);
    }

    printf("got entry of idx 3: %d\n", get_entry(head, 3));

    // 0->1->2->3->4->NULL
    head = reverse_list(head);

    for (int i = 0; i < 5; i++)
    {
        head = delete_first(head);
        print_list(head);
    }
    return 0;
}