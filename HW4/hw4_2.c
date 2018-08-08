#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//gcc --std=c99 -o hw4_2 hw4_2.c
//./hw4_2.c

int num=0;
int get_x(int n){
    int x=rand()%n;
    return x;
}
void sortcoin(int arr[],int n,int x){
    for(int i=0;i<n;i++){
        if(i==x)    arr[i]=0;
        else    arr[i]=1;
    }
}
void find_x(int arr[],int s,int n,int weighting){
    int a=((n-s)/3);
    int i,g1=0,g2=0,g3=0;

    for(i=s;i<a+s;i++){
        g1=g1+arr[i];
    }
    for(i=a+s;i<(2*a)+s;i++){
        g2=g2+arr[i];
    }
    for(i=(2*a)+s;i<n;i++){
        g3=g3+arr[i];
    }
    weighting++;
    if((n-s)>3){
        if(g1==g2){
            find_x(arr,s+(2*a),n,weighting);
        }
        else if(g1==g3){
            weighting++;
            find_x(arr,s+a,s+(2*a),weighting);
        }
        else{
            weighting++;
            find_x(arr,s,s+a,weighting);
        }
    }
    else{
        if(arr[s]==arr[s+1]){
            num= n;
            
        }else if(arr[s]==arr[n]){
            num= s+2;
            weighting++;
        }
        else {
            weighting++;
            num= s+1;
        }
        printf("\tnumber of weighting %d",weighting);//print the weighting time
    }
}
int main(int argc,char* argv[])
{
    clock_t start_time, end_time;
    float total_time = 0;
    int n;
    printf("enter a number\n");
    scanf("%d",&n);
    int weighting=0;
    int totalweight=0;
    int m=pow(3,n);
    start_time = clock(); //start timing
    int arr[m];
    int x=get_x(m);//randomly set the odd coin
    sortcoin(arr,m,x);//put coin into get
    find_x(arr,0,m,weighting);//find the odd coin
    end_time = clock();//stop timing
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;//get the running time
    printf(";%d coins cost %f sec\n",m,total_time);
    printf("\n\n");
}
