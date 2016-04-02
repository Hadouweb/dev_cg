#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct      s_lst
{
    char            *card;
    struct s_lst    *next;
    int             id_list;
}                   t_lst;

void    ft_debug_cards(char c[13][2])
{
    int     i;

    i = 0;
    while (i < 13)
    {
        fprintf(stderr, "%c %d\n", c[i][0], c[i][1]);
        i++;
    }
}

void    ft_debug_lst(t_lst *l, int id)
{
    fprintf(stderr, "Joueur %d : ", id);
    while (l)
    {
        fprintf(stderr, "%s[%d] ", l->card, l->id_list);
        l = l->next;
    }
    fprintf(stderr, "\n");
}

t_lst  *ft_create_node(char *card, int id_list)
{
    t_lst  *node;

    node = (char*)malloc(sizeof(t_lst));
    node->card = strndup(card, 2);
    node->card[1] = '\0';
    node->id_list = id_list;
    node->next = NULL;
    return (node);
}

void    ft_push_back(t_lst **lst, char *card, int id_list)
{
    t_lst   *l;

    l = *lst;
    if (l)
    {
        while (l->next)
            l = l->next;
        l->next = ft_create_node(card, id_list);
    }
    else
        *lst = ft_create_node(card, id_list);
}

void    ft_del_and_push(t_lst **lst1, t_lst **lst2, t_lst **fight_lst, int nb)
{
    int     i;
    t_lst   *l;


    i = 0;
    l = *fight_lst;
    while (i < nb && *lst1)
    {
        ft_push_back(fight_lst, (*lst1)->card, 1);
        (*lst1) = (*lst1)->next;
        i++;
    }
    i = 0;
    while (i < nb && *lst2)
    {
        ft_push_back(fight_lst, (*lst2)->card, 2);
        (*lst2) = (*lst2)->next;
        i++;
    }
}

int     ft_fight(t_lst **lst1, t_lst **lst2, t_lst **fight_lst, char c[13][2])
{
    int     c1;
    int     c2;
    int     i;
    //ft_debug_cards(c);
    i = 0;
    c1 = 0;
    c2 = 0;
    while (i < 13 && *lst1 && *lst2)
    {
        if ((*lst1)->card[0] == c[i][0])
            c1 = c[i][1];
        if ((*lst2)->card[0] == c[i][0])
            c2 = c[i][1];
        i++;
    }
    ft_del_and_push(lst1, lst2, fight_lst, 1);
    if (c1 > c2 || *lst1 && !*lst2)
        return (1);
    else if (c1 < c2 || *lst2 && !*lst1)
        return (2);
    else
    {
        ft_del_and_push(lst1, lst2, fight_lst, 3);
        ft_fight(lst1, lst2, fight_lst, c);
    }
   // fprintf(stderr, "c1 %d c2 %d\n", c1, c2);
}

void    ft_sort_fight_list(t_lst **fight_lst, t_lst **l)
{
    t_lst   *fl;
    t_lst   *tmp;

    fl = *fight_lst;
    while (fl)
    {
        if (fl->id_list == 1)
            ft_push_back(l, fl->card, 0);
        fl = fl->next;
    }
    fl = *fight_lst;
    while (fl)
    {
        if (fl->id_list == 2)
            ft_push_back(l, fl->card, 0);
        tmp = fl;
        fl = fl->next;
        free(tmp->card);
        free(tmp);
        tmp = NULL;
    }
}

void    ft_push_and_clear(t_lst **lst, t_lst **fight_lst)
{
    t_lst   *fl;
    t_lst   *l;
    t_lst   *tmp;
    t_lst   *new_fl;

    l = *lst;
    tmp = NULL;
    new_fl = NULL;
    ft_sort_fight_list(fight_lst, &new_fl);
    fl = new_fl;
    ft_debug_lst(fl, 3);
    while (fl)
    {
        ft_push_back(lst, fl->card, 0);
       // fprintf(stderr, "fl, %s\n", fl->card);
        tmp = fl->next;
        free(fl);
        fl = NULL;
        fl = tmp;
    }
    *lst = l;
    *fight_lst = NULL;
}

void    ft_loop(t_lst **lst1, t_lst **lst2, char c[13][2])
{
    int     i;
    int     win;
    t_lst   *fight_lst;

    fight_lst = NULL;
    while (*lst1 && *lst2)
    {
        win = ft_fight(lst1, lst2, &fight_lst, c);
        if (win == 1)
            ft_push_and_clear(lst1, &fight_lst);
        else
            ft_push_and_clear(lst2, &fight_lst);
        fprintf(stderr, "winner : %d\n", win);
        ft_debug_lst(*lst1, 1);
        ft_debug_lst(*lst2, 2);
        fprintf(stderr, "\n");
        i++;
    }
    if (win == 1)
        printf("1 %d\n", i);
    else if (win == 2)
        printf("2 %d\n", i);
    else if (win == 3)
        printf("PAT\n");
}

int     main()
{
    int     n; // the number of cards for player 1
    int     m; // the number of cards for player 2
    t_lst   *lst1;
    t_lst   *lst2;
    char    c[13][2] = {{'2', 0},{'3', 1},{'4', 2},{'5', 3},{'6', 4},{'7', 5},{'8', 6},{'9', 7},{'1', 8},
    {'J', 9},{'Q', 10},{'K', 11},{'A', 12},};

    lst1 = NULL;
    lst2 = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cardp1[2]; // the n cards of player 1
        scanf("%s", cardp1);
        ft_push_back(&lst1, cardp1, 1);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char cardp2[2]; // the m cards of player 2
        scanf("%s", cardp2);
        ft_push_back(&lst2, cardp2, 2);
    }
    ft_debug_lst(lst1, 1);
    ft_debug_lst(lst2, 2);
    ft_loop(&lst1, &lst2, &c);
    return 0;
}