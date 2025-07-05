#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

// 리스트 전체 출력
void print_list(ListNode *head)
{
    if (head == NULL) return;

    const ListNode *p = head->link; // head 다음이 처음 노드이다
    const ListNode *const start = p; // read-only target

    do
    {
        printf("%d->", p->data);
        p = p->link;
    } while (p != start);
}

ListNode* insert_first(ListNode *head, element data)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = data;

    if (head == NULL)
    {
        head = new_node;
        new_node->link = head;
        return head;
    }

    // head is not null
    new_node->link = head->link; // new_node가 이전의 첫 노드를 가리킨다
    head->link = new_node; // head가 진짜 첫 노드인 new_node를 가리킨다
    return head;
}


// alternative function
// ListNode* insert_last(ListNode *head, element data)
// {
//     head = insert_first(head, data);
//     head = head->link;
// }

// insert_first와 거의 유사, head를 data를 가지는 새 노드를 가리키게 함
ListNode* insert_last(ListNode *head, element data)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = data;

    if (head == NULL)
    {
        head = new_node;
        new_node->link = head;
        return head;
    }

    // head is not null
    new_node->link = head->link;
    head->link = new_node;
    head = new_node;

    return head;
}

int main(void)
{
    ListNode *head = NULL;

    // list = 10->20->30->40
    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);

    print_list(head);

    // memory will be leaked
    return 0;
}