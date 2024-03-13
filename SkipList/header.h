#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

typedef struct SkipListNode
{
    struct SkipListNode* next;
    struct SkipListNode* down;
    int data;
} Node;

typedef struct SkipListHead
{
    int level;
    struct SkipListNode* next;
    struct SkipListHead* down;
} Head;

void greeting();
void menu(Head* head);
void submenu(Head* head);
Node* create_node(int data);
Head* create_head(int level);
Node* insert_sorted(Head* head, int data);
Head* read_and_sort(Head* head, int mode);
int coin();
void add_levels(Head* head);
void insert_node(Head* head);
void delete_node(Node* node);
void delete_list_node(Head* head);
void print_list(Head* head);
void free_list(Head* head);
void end_prog();

#endif /* HEADER_H */
