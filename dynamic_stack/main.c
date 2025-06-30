#include <stdio.h>
#include <stdlib.h>

int const MAX_STACK_SIZE = 100;

typedef int element;
typedef struct
{
    element *data;
    int capacity;
    int top;
} StackType;

// 스택 생성
void init_stack(StackType *s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출
_Bool is_empty(StackType *s)
{
    return (s->top == -1);
}

// 포화 상태 검출
_Bool is_full(StackType *s)
{
    return (s->top == (s->capacity - 1));
}

void push(StackType *s, element item)
{
    // 스택이 포화 상태일 시 기존 크기의 2배로 스택 재할당
    if (is_full(s))
    {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }

    s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }

    return s->data[(s->top)--];
}

int main(void)
{
    StackType s;
    init_stack(&s);

    for (int i = 1; i <= 3; i++)
    {
        push(&s, i);
    }

    for (int i = 1; i <= 3; i++)
    {
        printf("%d \n", pop(&s));
    }

    free(s.data);
    return 0;
}