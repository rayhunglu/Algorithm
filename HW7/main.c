//
//  main.c
//  hw7
//
//  Created by lu juihung on 2/26/18.
//  Copyright © 2018 lu juihung. All rights reserved.
//  gcc -o main main.c

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
static int cx[8] = {1,1,2,2,-1,-1,-2,-2};
static int cy[8] = {2,-2,1,-1,2,-2,1,-1};
int N;

bool limits(int x, int y)
{
    return ((x >= 0 && y >= 0) && (x < N && y < N));
}

/* Checks whether a square is valid and empty or not */
bool isempty(int a[], int x, int y)
{
    return (limits(x, y)) && (a[y*N+x] < 0);
}

/* Returns the number of empty squares adjacent to (x, y) */
int nextMovenum(int a[], int x, int y)
{
    int count = 0;
    for (int i = 0; i < 8; ++i)
        if (isempty(a, (x + cx[i]), (y + cy[i])))
            count++;
    
    return count;
}

// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick next point.
bool nextMove(int a[], int *x, int *y)
{
    int min_deg_idx = -1, c, min_deg = (8+1), nx, ny;
    
    // Try all adjacent of (*x, *y), find the adjacent with minimum degree.
    int start = 0;
    for (int count = 0; count < 8; ++count)
    {
        int i = (start + count)%8;
        nx = *x + cx[i];
        ny = *y + cy[i];
        if ((isempty(a, nx, ny)) &&
            (c = nextMovenum(a, nx, ny)) < min_deg)
        {
            min_deg_idx = i;
            min_deg = c;
        }
    }
    
    // IF we could not find a next cell
    if (min_deg_idx == -1)
        return false;
    
    // Store coordinates of next point
    nx = *x + cx[min_deg_idx];
    ny = *y + cy[min_deg_idx];
    
    // Mark next move
    a[ny*N + nx] = a[(*y)*N + (*x)]+1;
    
    // Update next point
    *x = nx;
    *y = ny;
    
    return true;
}
/* checks the tour is closed if return ture*/
bool checkclosed(int x, int y, int xx, int yy)
{
    for (int i = 0; i < N; ++i)
        if (((x+cx[i]) == xx)&&((y + cy[i]) == yy))
            return true;
    
    return false;
}
int main()
{
    // To make sure that different random
    // initial positions are picked.
    srand(time(NULL));
    printf("enter a number\n");
    scanf("%d",&N);
    int a[N*N];
    for (int i = 0; i< N*N; ++i)
        a[i] = -1;
    
    // Randome initial position
    int sx = rand()%N;
    int sy = rand()%N;
    int x = sx, y = sy;
    // Mark first move.
            a[y*N+x] = 1;
    
    // Keep picking next points using Warnsdorff's heuristic
    for (int i = 0; i < N*N-1; ++i)
        if (nextMove(a, &x, &y) == 0){
            printf("\n<<can not find the tour>>\n");
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                    printf("%d\t",a[j*N+i]);
                printf("\n");
            }
            exit(0);
        }
    // Check if tour is closed
    if (!checkclosed(x, y, sx, sy)){
        printf("opened solution\n");
    }else{
        printf("closed solution\n");
    }
    //print
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%d\t",a[j*N+i]);
        printf("\n");
    }
    return 0;
}
