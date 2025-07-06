#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode
{
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// 순환적인 탐색 함수
TreeNode* search(TreeNode *node, element target)
{
    if (node == NULL) return NULL;
    if (target == node->key) return node;

    // 좌우 자식 탐색
    if (target < node->key)
    {
        return search(node->left, target);
    }

    // right
    return search(node->right, target);
}

TreeNode* create_node(element key)
{
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));

    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

TreeNode* insert_node(TreeNode *node, element key)
{
    if (node == NULL)
    {
        return create_node(key);
    }

    if (key < node->key)
    {
        node->left = insert_node(node->left, key);
    } else if (key > node->key)
    {
        node->right = insert_node(node->right, key);
    }

    return node;
}

TreeNode *min_value_node(TreeNode *node)
{
    TreeNode *curr = node;

    while (curr->left != NULL)
        curr = curr->left;

    return curr;
}

TreeNode *delete_node(TreeNode *root, element key)
{
    if (root == NULL) return NULL;

    if (key < root->key)
    {
        root->left = delete_node(root->left, key);
    } else if (key > root->key)
    {
        root->right = delete_node(root->right, key);
    }

    // key == root->key
    else
    {
        // 한 쪽 또는 양 쪽 트리 노드가 없는 경우
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        TreeNode *min_node = min_value_node(root->right);
        root->key = min_node->key;
        delete_node(root->right, min_node->key);
    }

    return root;
}

// 중위 순회
void inorder(TreeNode *root)
{
    if (root == NULL) return;

    inorder(root->left);
    printf("[%d] ", root->key);
    inorder(root->right);
}

int main(void)
{
    TreeNode *root = NULL;

    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);

    printf("이진 탐색 트리 중위 순회 결과\n");
    inorder(root);
    printf("\n\n");

    if (search(root, 30) != NULL)
        printf("이진 탐색 트리에서 30을 발견함");
    else
        printf("이진 탐색 트리에서 30을 발견 못 함");

    // memory will be leaked
    return 0;
}