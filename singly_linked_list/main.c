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

int main(void)
{
    ListNode *head = NULL;

    for (int i = 0; i < 5; i++)
    {
        head = insert_first(head, i);
        print_list(head);
    }

    printf("got entry of idx 3: %d\n", get_entry(head, 3));
    for (int i = 0; i < 5; i++)
    {
        head = delete_first(head);
        print_list(head);
    }
    return 0;
}