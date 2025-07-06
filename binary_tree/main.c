#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

#define MAX_QUEUE_SIZE 100
typedef TreeNode *element;
typedef struct
{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

_Bool is_empty(QueueType *q)
{
    return q->front == q->rear;
}

_Bool is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

void enqueue(QueueType *q, element item)
{
    if (is_full(q))
    {
        error("큐가 포화 상태입니다.");
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
    if (is_empty(q))
    {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

//       15
//    4      20
// 1       16   25

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

// 중위 순회 (LVR)
void inorder(TreeNode *root)
{
    if (root == NULL) return;

    inorder(root->left);
    printf("[%d] ", root->data);
    inorder(root->right);
}

// 전위 순회 (VLR)
void preorder(TreeNode *root)
{
    if (root == NULL) return;

    printf("[%d] ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// 후위 순회 (LRV)
void postorder(TreeNode *root)
{
    if (root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("[%d] ", root->data);
}

void level_order(TreeNode *ptr)
{
    QueueType q;
    init_queue(&q);

    if (ptr == NULL) return;

    enqueue(&q, ptr);
    while (!is_empty(&q))
    {
        ptr = dequeue(&q);
        printf("[%d] ", ptr->data);

        if (ptr->left != NULL)
        {
            enqueue(&q, ptr->left);
        }
        if (ptr->right != NULL)
        {
            enqueue(&q, ptr->right);
        }
    }
}

int main(void)
{
    printf("중위 순회 = ");
    inorder(root);
    printf("\n");

    printf("전위 순회 = ");
    preorder(root);
    printf("\n");

    printf("후위 순회 = ");
    postorder(root);
    printf("\n");

    printf("레벨 순회 = ");
    level_order(root);
    // printf("\n");
    return 0;
}