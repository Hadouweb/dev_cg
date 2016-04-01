#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct      s_node
{
    char            data;
    struct s_node   *next;
}                   node;

const static char tab[13] =
        {'2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K', 'A'};

static int count;

void    list_clear(node **cards)
{
    node    *list;
    node    *tmp;

    list = *cards;
    tmp = NULL;
    if (list)
    {
        while (list->next)
        {
            tmp = list;
            list = tmp->next;
            tmp->next = NULL;
            free(list);
        }
        *cards = NULL;
    }
    else
        *cards = NULL;
}

node    *add_card(char card)
{
    node    *c;

    c = (node *)malloc(sizeof(node));
    if (c)
    {
        c->data = card;
        c->next = NULL;
    }
    return (c);
}

void    list_push_back(node **cards, char card)
{
    node    *list;

    list = *cards;
    if (list)
    {
        while (list->next)
            list = list->next;
        list->next = add_card(card);
    }
    else
        *cards = add_card(card);
}

void    list_push_front(node **cards, char card)
{
    node    *list;
    node    *n;

    list = *cards;
    if (list)
    {
        n = add_card(card);
        n->next = list;
        *cards = n;
    }
    else
        *cards = add_card(card);
}

void    list_push_list(node **cards, node *l)
{
    node    *list;

    list = *cards;
    if (list)
    {
        while (list->next)
            list = list->next;
        while (l)
        {
            list->next = add_card(l->data);
            l = l->next;
            list = list->next;
        }
    }
    else
        *cards = l;
}

int     compare(char c1, char c2)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (tab[i] != c1)
        i++;
    while (tab[j] != c2)
        j++;
    return (i - j);
}

void    good_push(node **c1, node **c2, node **tmp1, node **tmp2, node **w)
{
    list_push_back(w, (*c2)->data);
    list_push_back(w, (*c1)->data);
    if (*tmp1)
    {
        list_push_list(w, *tmp2);
        list_push_list(w, *tmp1);
        list_clear(tmp1);
        list_clear(tmp2);
    }
    count++;
}

int     main()
{
    int     n;
    int     m;
    node    *c1;
    node    *c2;

    c1 = NULL;
    c2 = NULL;
    count = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cardp1[3];
        scanf("%s", cardp1);
        list_push_back(&c1, cardp1[0]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char cardp2[3];
        scanf("%s", cardp2);
        list_push_back(&c2, cardp2[0]);
    }

    node    *tmp1;
    node    *tmp2;

    tmp1 = NULL;
    tmp2 = NULL;
    while (c1 && c2)
    {
        //fprintf(stderr, "%c %c\n", c1->data, c2->data);
        if (compare(c1->data, c2->data) > 0)
            good_push(&c1, &c2, &tmp1, &tmp2, &c1);
        else if (compare(c1->data, c2->data) < 0)
            good_push(&c1, &c2, &tmp1, &tmp2, &c2);
        else if (compare(c1->data, c2->data) == 0)
        {
            int     b;

            b = 0;
            list_push_back(&tmp1, c1->data);
            list_push_back(&tmp2, c2->data);
            while (c1 && c2 && b < 3)
            {
                c1 = c1->next;
                c2 = c2->next;
                list_push_back(&tmp1, c1->data);
                list_push_back(&tmp2, c2->data);
                b++;
            }
        }
        c1 = c1->next;
        c2 = c2->next;
    }
    while (tmp2)
    {
        fprintf(stderr, "a %c\n", tmp2->data);
        tmp2 = tmp2->next;
    }
    fprintf(stderr, "%d %d %d\n", count, c1, c2);
    if (c1 && !c2)
        printf("1 %d\n", count);
    else if (c2 && !c1)
        printf("2 %d\n", count);
    else
        printf("PAT\n");
    return 0;
}