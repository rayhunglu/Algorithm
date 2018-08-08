//
//  main.c
//  5-1
//
//  Created by lu juihung on 2/14/18.
//  Copyright © 2018 lu juihung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main() {
        clock_t start, finish;

        int ordP1,ordP2;
        int Poly1[131072],Poly2[131072],Poly3[131072]={0};
        printf("the max power of the polynomia : ");
        scanf("%d",&ordP1);
//    ordP2=ordP1;
//        printf("coefficient of the polynomial 1:(from x^0 to x^n) ");
    for(int i=0;i<=ordP1;i++){
//        for(int i=0;i<=pow(2,aa);i++){
        scanf("%d",&Poly1[i]);}
        printf("the max power of the polynomial 2: ");
        scanf("%d",&ordP2);
        printf("coefficient of the polynomi16al 2:(from x^0 to x^n) ");
        for(int i=0;i<=ordP2;i++)
            scanf("%d",&Poly2[i]);
//        Poly1[i]=1;
//            Poly2[i]=1;}

    start=clock();
        for(int i=0;i<=ordP1;i++){
            for(int j=0;j<=ordP1;j++){
                Poly3[i+j]+=Poly1[i]*Poly2[j];
            }
        }
    finish=clock();
        //output the polynomial 3
        for(int i=ordP1+ordP2;i>=0;i--)
            printf("%d ",Poly3[i]);
    
    float duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf( "%f seconds\n", duration );        printf("\n");
        
    
        return 0;
}
