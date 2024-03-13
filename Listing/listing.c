#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct listing
{
    int data;
    struct listing *next, *down, *prev;
} list_in;

void distribution(int *string, int *top, int *bottom, int count, int *tc, int *bc)
{
    for(int i = 0; i < count; i++)
    {
        if(i%2 == 0)
        {
            bottom[*bc] = string[i];
            (*bc)++;
        }
        else if(i%2 == 1)
        {
            top[*tc] = string[i];
            (*tc)++;
        }
        else
        {
            printf("ошибка распределения!\n");
        }
    }
}

list_in *createNode(int data)
{
    list_in *node = (list_in*) malloc(sizeof(list_in));
    node->data = data;
    node->down = NULL;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

list_in *createRoof(int data, list_in **tail)
{
    list_in *node = (list_in*) malloc(sizeof(list_in));
    node->data = data;
    node->down = *tail;
    node->prev = NULL;
    (*tail) = (*tail)->prev;
    node->next = NULL;
    return node;
}

void addBottomElem(int data, list_in **head)
{
    list_in *new = createNode(data);
    (*head)->prev = new;
    new->next = *head;
    *head = new;
}

void addRoofElem(int data, list_in **tail, list_in **head)
{
    list_in *new = createRoof(data, tail);
    new->next = *head;
    *head = new;
}

int main()
{
    printf("Вводите последоватьельность чисел 'string' (0 = end && 0 ! 'string')\n");
    int *bottom = malloc(sizeof(int));
    int *top = malloc(sizeof(int));
    int bc = 0, tc = 0, num, count = 0, move;

    int *string = malloc(sizeof(int));
    while(scanf("%d", &num) && num != 0)
    {
        string[count] = num;
        count++;
    }

    distribution(string, top, bottom, count, &tc, &bc);

    free(string);

    printf("Созданный список выглядит так:\n");
    for(int i = tc-1; i >= 0; i--)
    {
        printf("%d ", top[i]);
    }
    printf("\n");
    
    for(int i = bc-1; i >= 0; i--)
    {
        printf("%d ", bottom[i]);
    }
    printf("\n");
    
    list_in *list = createNode(bottom[0]);
    list_in *tail = list;
    for(int i = 1; i < bc; i++)
    {
        addBottomElem(bottom[i], &list);
    }
    if(count%2 == 1)
    {
        tail = tail->prev;
    }
    list = createRoof(top[0], &tail);
    for(int i = 1; i < tc; i++)
    {
        addRoofElem(top[i], &tail, &list);
    }
    list_in *current = list;
    printf("\n");
    printf("Текущий элемент: %d\n", current->data);
    printf("Используйте 6 чтобы двигаться вправо или 2 чтобы двигаться вниз\nmove = ");
    while(scanf("%d", &move) && current != NULL)
    {
        if(move == 6 && current->next != NULL)
        {
            system("clear");
            printf("Созданный список выглядит так:\n");
            for(int i = tc-1; i >= 0; i--)
            {
                printf("%d ", top[i]);
            }
            printf("\n");
            for(int i = bc-1; i >= 0; i--)
            {
                printf("%d ", bottom[i]);
            }
            printf("\n");       
            printf("Текущий элемент: |%d|\n", current->next->data);
            printf("Используйте 6 чтобы двигаться вправо или 2 чтобы двигаться вниз\n");
            printf("move = ");
            current = current->next;
        }
        else if(move == 2 && current->down != NULL)
        {
            system("clear");
            printf("Созданный список выглядит так:\n");
            for(int i = tc-1; i >= 0; i--)
            {
                printf("%d ", top[i]);
            }
            printf("\n");
            for(int i = bc-1; i >= 0; i--)
            {
                printf("%d ", bottom[i]);
            }
            printf("\n"); 
            printf("Текущий элемент: |%d|\n", current->down->data);
            printf("Используйте 6 чтобы двигаться вправо или 2 чтобы двигаться вниз\n");
            printf("move = ");
            current = current->down;
        }
        else if(current->next == NULL && current->down == NULL)
        {
            break;
        }
        else
        {
            printf("Вы не можете туда перейти\n");
        }
    }
    printf("Вы вышли из списка\n");
    free(bottom);
    free(top);
    return 0;
}