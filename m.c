#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct  s_elev
{
    int         y;
    int         x;
}               t_elev;

typedef struct  s_app
{
    int         map_y;
    int         map_x;
    int         nb_rounds;
    int         exit_y;
    int         exit_x;
    int         nb_total_clones;
    int         nb_elevators;
    int         nb_additional_elevators;
    int         y;
    int         stop_left;
    int         stop_right;
    int         dist;
    int         new_y;
    int         block;
    int         init_x;
    t_elev      *elev;
    t_elev      current_elev;
}               t_app;

typedef struct      s_clone
{
    int             y;
    int             x;
    char            direction[10];
}                   t_clone;

void    ft_debug(t_app *app)
{
    int     i;

    i = 0;
    while (i < app->nb_elevators)
    {
        fprintf(stderr, "elev y x : %d %d\n", app->elev[i].y, app->elev[i].x);
        i++;
    }
    fprintf(stderr, "exit y x : %d %d\n", app->exit_y, app->exit_x);
}

void    ft_debug_clone(t_clone *clone, t_app *app)
{
    fprintf(stderr, "clone y x : %d %d\n", clone->y, clone->x);
    fprintf(stderr, "direction du clone : %s\n", clone->direction);
    fprintf(stderr, "elev y x : %d %d\n", app->current_elev.y, app->current_elev.x);
}

void    ft_set_current_elev(t_app *app, int y)
{
    int     i;

    i = 0;
    while (i < app->nb_elevators)
    {
        if (app->elev[i].y == y)
            app->current_elev = app->elev[i];
        i++;
    }
}

void    ft_choice(t_app *app, t_clone *clone)
{
    if (app->current_elev.x == clone->x)
        ft_set_current_elev(app, clone->y);
    if (clone->y == app->exit_y)
    {
        app->current_elev.x = app->exit_x;
        app->current_elev.y = app->exit_y;
    }
    if (clone->y == -1)
        printf("WAIT\n");
    else if (strcmp(clone->direction, "LEFT") == 0 && app->current_elev.x > clone->x &&
        app->current_elev.y == clone->y)
        printf("BLOCK\n");
    else if (strcmp(clone->direction, "RIGHT") == 0 && app->current_elev.x < clone->x &&
        app->current_elev.y == clone->y)
        printf("BLOCK\n");
    else
        printf("WAIT\n");
}

void    ft_loop(t_app *app)
{
    t_clone     clone;
    int         init;

    init = 1;
    while (1)
    {
        scanf("%d%d%s", &clone.y, &clone.x, &clone.direction);
        if (init)
        {
            app->y = clone.y;
            init = 0;
        }
        ft_choice(app, &clone);
        ft_debug_clone(&clone, app);
    }
}

int     main()
{
    t_app   app;
    int     i;

    bzero(&app, sizeof(t_app));
    scanf("%d%d%d%d%d%d%d%d", &app.map_y, &app.map_x, &app.nb_rounds, &app.exit_y,
        &app.exit_x, &app.nb_total_clones, &app.nb_additional_elevators, &app.nb_elevators);
    app.elev = (t_elev*)malloc(app.nb_elevators * sizeof(t_elev));
    i = 0;
    while (i < app.nb_elevators)
    {
        scanf("%d%d", &app.elev[i].y, &app.elev[i].x);
        i++;
    }
    ft_set_current_elev(&app, 0);
    ft_debug(&app);
    ft_loop(&app);
}