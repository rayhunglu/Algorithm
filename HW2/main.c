#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//recursive
void Hanoirecursive(int n, char head, char mid, char tail)
{
//    printf("Hanoi(%d,%c,%c,%c)\n",n,head,mid,tail);     //if you want to know all the movement in the recursive program
    if (n == 1){
        printf("Move disk 1 from %c to %c\n", head, tail);
        return;
    }
    Hanoirecursive(n-1, head, tail, mid);
    printf("Move disk %d from %c to %c\n", n, head, tail);
    Hanoirecursive(n-1, mid, head, tail);
}

//iterative
struct Stack
{
    int capacity;
    int top;
    int *array;
};

struct Stack* newStack(int n2)
{
    struct Stack* stack =(struct Stack*) malloc(sizeof(struct Stack));
    stack -> capacity = n2;
    stack -> top = -1;
    stack -> array =malloc(stack -> capacity * sizeof(int));
    return stack;
}

void push(struct Stack *stack, int item)
{
    if (stack->top == stack->capacity - 1)
        return;
    else stack -> array[++stack -> top] = item;
}

int pop(struct Stack* stack)
{
    if (stack->top == -1)
        return 0;
    else return stack -> array[stack -> top--];
}
// Function to implement legal movement between
// two poles
void moveDisk(struct Stack *st,struct Stack *end, char s, char d)
{
    int pole1TopDisk = pop(st);
    int pole2TopDisk = pop(end);

    if (pole1TopDisk == 0)
    {
        push(st, pole2TopDisk);
//        printf("Move disk %d from %c to %c\n",pole2TopDisk, d, s);  //if you want to know iterative program movement
    }
    else if (pole2TopDisk == 0)
    {
        push(end, pole1TopDisk);
//        printf("Move disk %d from %c to %c\n",pole1TopDisk, s, d);  //if you want to know iterative program movement

    }
    else if (pole1TopDisk > pole2TopDisk)
    {
        push(st, pole1TopDisk);
        push(st, pole2TopDisk);
//        printf("Move disk %d from %c to %c\n",pole2TopDisk, d, s);  //if you want to know iterative program movement
    }
    else
    {
        push(end, pole2TopDisk);
        push(end, pole1TopDisk);
//        printf("Move disk %d from %c to %c\n",pole1TopDisk, s, d);  //if you want to know iterative program movement
    }
}

void HanoiIterative(int disks, struct Stack *st, struct Stack *mid, struct Stack *end)
{
    int i, totalmovement;
    char a = 'A', b = 'B', c = 'C';

    //If number of disks is even, then interchange destination pole and auxiliary pole
    if (disks % 2 == 0)
    {
        char temp = c;
        c = b;
        b  = temp;
    }
    totalmovement = pow(2, disks) - 1;

    for (i = disks; i >= 1; i--)
        push(st, i);

    for (i = 1; i <= totalmovement; i++)
    {
        if (i % 3 == 1)
            moveDisk(st, end, a, c);

        else if (i % 3 == 2)
            moveDisk(st, mid, a, b);

        else if (i % 3 == 0)
            moveDisk(mid, end, b, c);
    }
}

int main()
{
    clock_t start1, end1;
    
    int n=30;                       //number of disks
    int n1,n2;
    printf("recursive\n");
    for(n1=1;n1<=n;n1++){           // run from 1 disk to n disks, if you want to only run nth disks, just remove the forloop and replace the n1 by n
        start1 = clock();
        Hanoirecursive(n1, 'A', 'B', 'C');
        end1 = clock();
        
        double diff1 = end1 - start1; // ms
        printf(" %d disk cost %f  sec\n", n1,diff1 / CLOCKS_PER_SEC );
    }
    printf(" -------------------------\n");
    printf("iterative\n");
    clock_t start2, end2;

    for(n2=1;n2<=n;n2++){           // run from 1 disk to n disks, if you want to only run nth disks, just remove the forloop and replace the n1 by n
    start2 = clock();

    struct Stack *st = newStack(n2);
    struct Stack *mid = newStack(n2);
    struct Stack *end = newStack(n2);

    HanoiIterative(n2, st, mid, end);
    end2 = clock();
    double diff2 = end2 - start2; // ms
    printf(" %d disk cost %f  sec\n", n2,diff2 / CLOCKS_PER_SEC );
    }
    printf("done\n");
    return 0;
}

