#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct  s_app
{
    int         map_y; // number of floors
    int         map_x; // width of the area
    int         nb_rounds; // maximum number of rounds
    int         exit_y; // floor on which the exit is found
    int         exit_x; // position of the exit on its floor
    int         nb_total_clones; // number of generated clones
    int         nb_additional_elevators; // ignore (always zero)
    int         nb_elevators; // number of elevators
    int         start_x;
    int         start_y;
    int         stop_left;
    int         stop_right;
    int         new_y;
}               t_app;

typedef struct      s_clone
{
    int             y;
    int             x;
    char            direction[10];
}                   t_clone;

void    ft_debug_data(t_app *app)
{
    fprintf(stderr, "map_y : %d\n", app->map_y);
    fprintf(stderr, "map_x : %d\n", app->map_x);
    fprintf(stderr, "nombre maximum de tours : %d\n", app->nb_rounds);
    fprintf(stderr, "exit y : %d\n", app->exit_y);
    fprintf(stderr, "exit x : %d\n", app->exit_x);
    fprintf(stderr, "le nombre de clones qui sortiront : %d\n", app->nb_total_clones);
    //fprintf(stderr, "0 : %d\n", app->nb_additional_elevators);
    fprintf(stderr, "le nombre d'ascenseurs présents : %d\n", app->nb_elevators);
    fprintf(stderr, "depart y x : %d %d\n", app->start_y, app->start_x);
}

void    ft_debug_clone(t_clone *clone, t_app *app)
{
    fprintf(stderr, "clone y : %d\n", clone->y);
    fprintf(stderr, "clone x : %d\n", clone->x);
    fprintf(stderr, "direction du clone : %s\n", clone->direction);
    fprintf(stderr, "tours restants : %d\n", app->nb_rounds);
    fprintf(stderr, "stop_left : %d\n", app->stop_left);
    fprintf(stderr, "stop_right : %d\n", app->stop_right);
    fprintf(stderr, "start x y: %d %d\n", app->start_x, app->start_y);
}


void    ft_stop(t_app *app, t_clone *clone)
{
    if (clone->y > app->start_y)
    {
        app->start_y = clone->y;
        app->start_x = clone->x;
        app->new_y = 1;
        fprintf(stderr, "___x: %d\n", app->start_x);
        if ((app->nb_rounds - app->map_y) / app->map_y < app->map_y - 1)
        {
            app->stop_right = (app->nb_rounds - app->map_y) / app->map_y + app->start_x - 1;
            app->stop_left =  app->start_x - ((app->nb_rounds - app->map_y) / app->map_y) + 1;
        }
        else
        {
            app->stop_right = app->map_x - 1;
            app->stop_left = 0;
        }
    }
    else
         app->new_y = 0;
    fprintf(stderr, "dist max : %d\n", ((app->nb_rounds - app->map_y) / app->map_y) - 1);
}

void    ft_choice(t_app *app, t_clone *clone)
{
    ft_stop(app, clone);
    if (clone->y == -1)
        printf("WAIT\n");
    else if (app->exit_y != clone->y)
    {
        if (!strcmp(clone->direction, "LEFT") && clone->x <= app->stop_left && clone->y == app->start_y)
        {
            printf("BLOCK\n");
            fprintf(stderr, "BLOCK1\n");
            app->stop_left = app->start_x;
        }
        else if (!strcmp(clone->direction, "RIGHT") && clone->x >= app->stop_right && clone->y == app->start_y)
        {
            printf("BLOCK\n");
            fprintf(stderr, "BLOCK2\n");
            app->stop_right = app->start_x;
        }
        else
            printf("WAIT\n");
    } 
    else
    {
        //if (clone->y == app->start_y && clone->x == app->start_x)
        //    printf("WAIT\n");
        if (app->exit_x < clone->x && strcmp(clone->direction, "RIGHT") == 0)
            printf("BLOCK\n");
        else if (app->exit_x > clone->x && strcmp(clone->direction, "LEFT") == 0)
            printf("BLOCK\n");
        else
            printf("WAIT\n");
        fprintf(stderr, "BLOCK3\n");
    }
    //app->nb_rounds--;
}

void    ft_loop(t_app *app)
{
    t_clone     clone;
    int         i;
    int         init;

   // clone = (t_clone*)malloc(app->nb_total_clones * sizeof(t_clone));
    i = 0;
    init = 0;
    while (1)
    {
        scanf("%d%d%s", &clone.y, &clone.x, &clone.direction);
        if (init == 0)
        {
            app->start_y = clone.y;
            app->start_x = clone.x;
            init = 1;
        }
        ft_choice(app, &clone);
        ft_debug_clone(&clone, app);
        i++;
    }
}

int     main()
{
    t_app   app;
    int     elevator_floor;
    int     elevator_pos;
    int     i;

    bzero(&app, sizeof(t_app));
    elevator_floor = 0;
    elevator_pos = 0;
    scanf("%d%d%d%d%d%d%d%d", &app.map_y, &app.map_x, &app.nb_rounds, &app.exit_y,
        &app.exit_x, &app.nb_total_clones, &app.nb_additional_elevators, &app.nb_elevators);
    //ft_stop(&app);
    app.stop_right = app.map_x - 1;
    i = app.nb_elevators;
    while (i--)
        scanf("%d%d", &elevator_floor, &elevator_pos);
    ft_debug_data(&app);
    ft_loop(&app);
}