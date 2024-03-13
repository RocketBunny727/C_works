#include "header.h"

#define MAX_LEVEL 3

void greeting()
{
    Head* head = create_head(0);
    int ch;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    move(10, 0);
    printw
    (
        "           __      __       .__                                                                                                                                             \n"
        "          /  \\    /  \\ ____ |  |   ____  ____   _____   ____                                                                                                                \n"
        "          \\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\                                                                                                               \n"
        "           \\        /\\  ___/|  | \\  \\__(  <_> )  Y Y  \\  ___/                                                                                                               \n"
        "            \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >                                                                                                              \n"
        "                 __                                                                                                                                                              \n"
        "               _/  |_  ____                                                                                                                                                      \n"
        "               \\   __ /  _ \\                                                                                                                                                     \n"
        "                |  | (  <_> )                                                                                                                                                    \n"
        "                |__|  \\____/                                                                                                                                                     \n\n"
        "            _____________  __._____________.____    .___  ____________________ ___.           __________               __           __ __________                           \n"
        "           /   _____/    |/ _|   \\______   \\    |   |   |/   _____/\\__    ___/ \\_ |__ ___.__. \\______   \\ ____   ____ |  | __ _____/  |\\______   \\__ __  ____   ____ ___.__.\n"
        "           \\_____  \\|      < |   ||     ___/    |   |   |\\_____  \\   |    |     | __ <   |  |  |       _//  _ \\ / ___\\|  |/ // __ \\   __\\    |  _/  |  \\/    \\ /    <   |  |\n"
        "           /        \\    |  \\|   ||    |   |    |___|   |/        \\  |    |     | \\_\\ \\___  |  |    |   (  <_> )  \\___|    <\\  ___/|  | |    |   \\  |  /   |  \\   |  \\___  |\n"
        "          /_______  /____|__ \\___||____|   |_______ \\___/_______  /  |____|     |___  / ____|  |____|_  /\\____/ \\___  >__|_ \\\\___  >__| |______  /____/|___|  /___|  / ____|\n\n\n\n"
        "                                                                                PRESS ON KEYPAD TO START WORK OR ANY BUTTON TO EXIT:)"
    );
    refresh();
    ch = getch();
    if(ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
    {
        endwin();
        menu(head);
    }
    else
    {
        endwin();
        end_prog();
    }
}

void menu(Head* head)
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    int height = 10;
    int width = 32;
    int y = (LINES - height) / 2;
    int x = (COLS - width) / 2;
    WINDOW* menuwin = newwin(height, width, y, x);
    int ch;
    int current_choice = 0;
    const char* menu_choices[] = {"Make List", "Insert node", "Delete node", "EXIT"};

    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == current_choice)
                mvwprintw(menuwin, 2 + i, 8, "-> %s\n", menu_choices[i]);
            else
                mvwprintw(menuwin, 2 + i, 8, "   %s\n", menu_choices[i]);
        }

        box(menuwin, 0, 0);
        wrefresh(menuwin);

        ch = getch();

        switch (ch)
        {
            case KEY_UP:
                current_choice--;
                if (current_choice < 0) current_choice = 0;
                break;
            case KEY_DOWN:
                current_choice++;
                if (current_choice > 3) current_choice = 3;
                break;
        }

        if (ch == 10)
        {
            delwin(menuwin);
            menuwin = NULL;
            if (current_choice == 3)
            {
                endwin();
                end_prog();
            }
            else
            {
                switch (current_choice)
                {
                case 0:
                    submenu(head);
                    break;
                case 1:
                    insert_node(head);
                    print_list(head);
                    break;
                case 2:
                    delete_list_node(head);
                    print_list(head);
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }
    free_list(head);
}

void submenu(Head* head)
{
    const char* submenu_choices[] = {"Input by keyboard", "Input by file", "Back"};
    int submenu_height = 10;
    int submenu_width = 32;
    int submenu_y = (LINES - submenu_height) / 2;
    int submenu_x = (COLS - submenu_width) / 2;
    int ch;
    int current_choice = 0;

    WINDOW* submenuwin = newwin(submenu_height, submenu_width, submenu_y, submenu_x);

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == current_choice)
            {
                mvwprintw(submenuwin, 2 + i, 5, "-> %s", submenu_choices[i]);
            }
            else
            {
                mvwprintw(submenuwin, 2 + i, 5, "   %s", submenu_choices[i]);
            }
        }

        box(submenuwin, 0, 0);
        wrefresh(submenuwin);

        ch = getch();

        switch (ch)
        {
            case KEY_UP:
                current_choice--;
                if (current_choice < 0) current_choice = 0;
                break;
            case KEY_DOWN:
                current_choice++;
                if (current_choice > 2) current_choice = 1;
                break;
        }

        if (ch == 10)
        {
            delwin(submenuwin);
            submenuwin = NULL;
            endwin();
            system("clear");
            switch(current_choice)
            {
                case 0:
                    head = read_and_sort(head, 0);
                    add_levels(head);
                    print_list(head);
                    break;
                
                case 1:
                    head = read_and_sort(head, 1);
                    add_levels(head);
                    print_list(head);
                    break;

                case 2:
                    menu(head);
                    break;
            }
            break;
        }
    }
}


Head* create_head(int level) //создание узла
{
    Head* head = (Head*)malloc(sizeof(Head));
    head->level = level;
    head->next = NULL;
    head->down = NULL;
    return head;
}

Node* create_node(int data) //создание головы
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->down = NULL;
    return new_node;
}

Node* insert_sorted(Head* head, int data)
{
    Node* new_node = create_node(data);

    if(head->next == NULL || head->next->data >= data)
    {
        new_node->next = head->next;
        head->next = new_node;
    }
    else
    {
        Node* current_node = head->next;
        while (current_node->next != NULL && current_node->next->data < data)
        {
            current_node = current_node->next;
        }
        new_node->next = current_node->next;
        current_node->next = new_node;
    }

    return new_node;
}

Head* read_and_sort(Head* head, int mode) //создание нижнего упорядоченного уроня
{
    int data, n;
    Head* current_head = head;
    Head* upper_head;

    if(mode == 0)
    {
        printf("Enter number of nodes on bottom: ");
        scanf("%d", &n);
        printf("Enter the nodes data: ");
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &data);
            insert_sorted(head, data);
        }
    }
    else if(mode == 1)
    {
        char filename[100];
        printf("Enter data filename: ");
        scanf("%s", filename);

        FILE* file = fopen(filename, "r");

        if (file == NULL)
        {
            printf("Failed to open the file '%s' for reading\n", filename);
            exit(0);
        }
        else
        {
            while (fscanf(file, "%d", &data) == 1)
            {
                insert_sorted(head, data);
            }

            fclose(file);
        }       
    }

    for(int i = 1; i <= MAX_LEVEL; i++)
    {
        Head* upper_head = create_head(i);
        upper_head->down = current_head;
        current_head = upper_head;
    }

    return current_head;
}

int coin()
{
    int x = rand() % 100 + 1;

    if(x > 50)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void add_levels(Head* head)
{
    Head* current_head = head;
    Node* current_node;
    Node* current_bottom_node;
    Head* level_heads[MAX_LEVEL + 1]; //массив указателей на головы уровней

    for(int i = MAX_LEVEL; i >= 0; i--)
    {
        level_heads[i] = current_head;
        current_head = current_head->down;
    }
    current_bottom_node = level_heads[0]->next;

    while(current_bottom_node != NULL)
    {
        current_node = current_bottom_node;
        for(int i = 1; i <= MAX_LEVEL; i++)
        {
            if(coin() == 1)
            {
                Node* new_node = insert_sorted(level_heads[i], current_bottom_node->data);
                new_node->down = current_node;
                current_node = new_node;
            }
            else
            {
                break;
            }
        }
        current_bottom_node = current_bottom_node->next;
    }
}

void insert_node(Head* head)
{
    int data, x;
    Head* current_head = head;
    Node* current_node;
    Node* down_node;
    Head* level_heads[MAX_LEVEL + 1];

    endwin();
    system("clear");
    printf("Enter data of new node: ");
    scanf("%d", &data);

    for (int i = MAX_LEVEL; i >= 0; i--)
    {
        level_heads[i] = current_head;
        current_head = current_head->down;
    }
    current_head = level_heads[MAX_LEVEL];

    while(1)
    {
        if(current_head->next == NULL || current_head->next->data >= data)
        {
            if(current_head->level > 0)
            {
                current_head = current_head->down;
            }
            else if(current_head->level == 0)
            {
                Node* new_node = create_node(data);
                new_node->next = current_head->next;
                current_head->next = new_node;
                down_node = new_node;
                break;
            }
            
        }
        else
        {
            current_node = current_head->next;
            while(1)
            {
                if(current_node->next == NULL || current_node->next->data >= data)
                {
                    if(current_node->down != NULL)
                    {
                        current_node = current_node->down;
                    }
                    else
                    {
                        Node* new_node = create_node(data);
                        new_node->next = current_node->next;
                        current_node->next = new_node;
                        down_node = new_node;
                        break;
                    }
                }
                else
                {
                    current_node = current_node->next;
                }
            }
            break;
        }
        
    }

    for(int i = 1; i <= MAX_LEVEL; i++)
    {
        if(coin() == 1)
        {
            current_node = insert_sorted(level_heads[i], data);
            current_node->down = down_node;
            down_node = current_node;
        }
        else
        {
            break;
        }
    }
}

void delete_list_node(Head* head)
{
    int data;
    Head* current_head = head;
    Node* current_node;

    endwin();
    system("clear");
    printf("Enter data of node: ");
    scanf("%d", &data);

    while(1)
    {
        if(current_head->next == NULL || current_head->next->data > data)
        {
            if(current_head->down != NULL)
            {
                current_head = current_head->down;
            }
            else
            {
                printf("Node not found\n");
                break;
            }
        }
        else if(current_head->next->data == data)
        {
            Node* temp = current_head->next;
            current_head->next = temp->next;
            temp->down = NULL;
            free(temp);
            if(current_head->down != NULL)
            {
                current_head = current_head->down;
            }
            else
            {  
                break;
            }
        }
        else if(current_head->next->data < data)
        {
            current_node = current_head->next;
            while(1)
            {
                if(current_node->next == NULL || current_node->next->data > data)
                {
                    if(current_node->down != NULL)
                    {
                        current_node = current_node->down;
                    }
                    else
                    {
                        printf("Node not found\n");
                        break;
                    }
                }
                else if(current_node->next->data < data)
                {
                    current_node = current_node->next;
                }
                else if(current_node->next->data == data)
                {
                    Node* temp = current_node->next;
                    current_node->next = temp->next;
                    temp->down = NULL;
                    free(temp);
                    if(current_node->down != NULL)
                    {
                        current_node = current_node->down;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        }
    }
}

void print_list(Head* head)
{
    int ch;
    Head* current_head = head;
    Node* current_node = current_head->next;

    for(int i = MAX_LEVEL; i >= 0; i--)
    {
        printf("LVL#%d: ", current_head->level);

        while(current_node != NULL)
        {
            printf("%d ", current_node->data);
            current_node = current_node->next;
        }

        printf("\n");

        if (current_head->down != NULL)
        {
            current_head = current_head->down;
            current_node = current_head->next;
        }
        else
        {
            break;
        }
    }

    printf("\nChoose next action\n1.Go to menu\n2.Exit\n");
    scanf("%d", &ch);

    if(ch == 1)
    {
        menu(head);
    }
    else
    {
        free_list(head);
        end_prog();
    }
}

void free_list(Head* head)
{
    Head* current_head = head;
    while(current_head != NULL)
    {
        Node* current_node = current_head->next;
        while (current_node != NULL)
        {
            Node* temp_node = current_node;
            current_node = current_node->next;
            temp_node->down = NULL;
            free(temp_node);
        }
        Head* temp_head = current_head;
        current_head = current_head->down;

        temp_head->down = NULL;

        free(temp_head);
    }
    printf("Clear!\n");
}


void end_prog()
{
    printf("Thanks for using!!!\n");
    exit(0);
}