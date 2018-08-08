#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//gcc --std=c99 -o hw4-1 hw4-1.c
//./hw4-1.c n   //(2^n)


struct tri{
    int x,y;
};
//choose the X location randomly
struct tri *get_x(int side){
    printf("Matrix:%d*%d\n",side,side);
    srand(time(NULL));
    struct tri *tri = malloc(sizeof(struct tri));
    tri->x = rand()%side;
    tri->y = rand()%side;
    printf("X is in [%d, %d] \n", tri->x, tri->y);
    return tri;
}

//create a array to show the game's board
char **getborad(struct tri *tri,int side){
    int i,j;
    printf("Get Board \n");
    char **board=malloc(sizeof(char*)*side);
    for(int i=0;i<side;i++){
        board[i] = malloc(sizeof(char)*side);
    }
    for(i=0;i<side;i++)
    {
        for(j=0;j<side;j++)
        {
            if(i == tri->x && j==tri->y)
            {
                board[i][j] ='X';
                printf("%c\t",board[i][j]);
            }
            else
            {
                board[i][j] = '_';
                printf("%c\t",board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return board;
}
//start to solve problem
int put_tri(char **board,int x,int y,int n,int side,int markx,int marky){
    int center=side/2;
    int sx=x+center-1;
    int bx=x+center;
    int sy=y+center-1;
    int by=y+center;
    if (side == 2)
    {
        board[x][y] = n;
        board[x][y + 1] = n;
        board[x + 1][y] = n;
        board[x + 1][y + 1] = n;
        board[markx][marky] = -1;
        return n += 1;
    }
    else{
        if (markx < bx && marky < by)//bottom right
        {
            n = put_tri(board,x,y,n,center,markx,marky);
            n = put_tri(board,bx,y,n,center,bx,sy);
            n = put_tri(board,bx,by,n,center,bx,by);
            n = put_tri(board,x,by,n,center,sx,by);
            
            board[sx][by] = n;
            board[bx][by] = n;
            board[bx][sy] = n;
        }
        else if (markx >= bx && marky < by)//top right
        {
            n = put_tri(board,x,y,n,center,sx,sy);
            n = put_tri(board,bx,y,n,center,markx,marky);
            n = put_tri(board,bx,by,n,center,bx,by);
            n = put_tri(board,x,by,n,center,sx,by);
            
            board[sx][sy] = n;
            board[bx][by] = n;
            board[sx][by] = n;
        }
        else if (markx >= bx && marky >= by)//top left
        {
            n = put_tri(board,x,y,n,center,sx,sy);
            n = put_tri(board,bx,y,n,center,bx,sy);
            n = put_tri(board,bx,by,n,center,markx,marky);
            n = put_tri(board,x,by,n,center,sx,by);
            board[sx][by] = n;
            board[sx][sy] = n;
            board[bx][sy] = n;
        }
        else if (markx < bx && marky >= by)//bottom left
        {
            n = put_tri(board,x,y,n,center,sx,sy);
            n = put_tri(board,bx,y,n,center,bx,sy);
            n = put_tri(board,bx,by,n,center,bx,by);
            n = put_tri(board,x,by,n,center,markx,marky);
            board[sx][sy] = n;
            board[bx][by] = n;
            board[bx][sy] = n;
        }
        return n += 1;
    }
}
//print the array to show the result
void print_board(char **board,int side){
    int i, j;
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            if (board[i][j] != -1)
                printf("%d\t", board[i][j]);
            else
                printf("x\t");
        }
        printf("\n");
    }
    for (i = 0; i < side; i++)
    {
        free(board[i]);
    }
    free(board);
}
int main(int argc,char* argv[])
{
    clock_t start_time, end_time;
    float total_time = 0;
    if(argc == 2)
    {
        int n = atoi(argv[1]);
            start_time = clock();
            int side=pow(2,n);
            struct tri *tri=get_x(side);
            char **board= getborad(tri,side);
            put_tri(board, 0, 0, 1,side, tri->x, tri->y);
            print_board(board, side);
            end_time = clock();
            total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
            printf("Board size %d * %d spend %f sec\n",side,side,total_time);
    }
    else
    {
        printf("please enter one argument.\n");
    }
    return 0;
}
