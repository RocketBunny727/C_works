#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BinarTree
{
    int data;
    struct BinarTree* left;
    struct BinarTree* right;
} BinarTree;

BinarTree* createNode(int value)
{
    BinarTree* node = (BinarTree*)malloc(sizeof(BinarTree));
    if (node)
    {
        node->data = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void insert(BinarTree** root, int value)
{
    if (*root == NULL)
    {
        *root = createNode(value);
    }
    else
    {
        if (value < (*root)->data)
        {
            insert(&(*root)->left, value);
        }
        else if (value > (*root)->data)
        {
            insert(&(*root)->right, value);
        }
    }
}

int isUnique(BinarTree* root, int value)
{
    if (root == NULL)
    {
        return 1; // значение уникально
    }
    
    if (value == root->data)
    {
        return 0; // значение уже существует в дереве
    }
    
    if (value < root->data)
    {
        return isUnique(root->left, value);
    }
    else
    {
        return isUnique(root->right, value);
    }
}

void destroyTree(BinarTree* root)
{
    if (root == NULL)
    {
        return;
    }
    
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int main()
{
    char filename[100];
    int n, min, max;

    srand(time(NULL));

    printf("Welcome to data maker\nEnter data file name: ");
    scanf("%s", filename);
    printf("Enter number of numbers: ");
    scanf("%d", &n);
    printf("Enter minimum value: ");
    scanf("%d", &min);
    printf("Enter maximum value: ");
    scanf("%d", &max);

    if (min > max || (max - min + 1) < n)
    {
        printf("Invalid input. Please make sure min <= max and (max - min + 1) >= n.\n");
        return 1;
    }

    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return 1;
    }

    BinarTree* root = NULL;

    for (int i = 0; i < n; i++)
    {
        int random_number;
        do 
        { 
            random_number = rand() % (max - min + 1) + min; 
        } while (!isUnique(root, random_number));
        
        insert(&root, random_number);
        fprintf(file, "%d\n", random_number);
    }

    printf("DONE!!!\n");
    fclose(file);
    destroyTree(root);

    return 0;
}