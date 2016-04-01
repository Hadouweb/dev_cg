#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    int *elevator;
    
    scanf("%d%d%d%d%d%d%d%d", &nbFloors, &width, &nbRounds, &exitFloor, &exitPos, &nbTotalClones, &nbAdditionalElevators, &nbElevators);
    elevator = (int*)malloc(nbElevators * sizeof(int));
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        scanf("%d%d", &elevatorFloor, &elevatorPos);
        elevator[elevatorFloor] = elevatorPos;
    }
    elevator[exitFloor] = exitPos;

    // game loop
    while (1) {
        int     cloneFloor; // floor of the leading clone
        int     clonePos; // position of the leading clone on its floor
        char    direction[2]; // direction of the leading clone: LEFT or RIGHT
        scanf("%d%d%s", &cloneFloor, &clonePos, direction);
        
        if (cloneFloor == -1 || elevator[cloneFloor] == clonePos
            || ((direction[0] == 'L') && (elevator[cloneFloor] < clonePos))
            || ((direction[0] == 'R') && (elevator[cloneFloor] > clonePos)))
            printf("WAIT\n"); // action: WAIT or BLOCK
        else
            printf("BLOCK\n"); // action: WAIT or BLOCK   
    }

    return 0;
}