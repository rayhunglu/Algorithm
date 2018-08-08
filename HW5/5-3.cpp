//5-3
#include<cstdio>
#include <cmath>
#include <iostream>
#include <time.h>
const int MAXN = 4 * 1e5 + 10;
struct Complex
{
    double r, i;
    Complex() {}
    Complex(double _r, double _i) { r = _r; i = _i; }
    Complex operator +(const Complex &y) { return Complex(r + y.r, i + y.i); }
    Complex operator -(const Complex &y) { return Complex(r - y.r, i - y.i); }
    Complex operator *(const Complex &y) { return Complex(r*y.r - i * y.i, r*y.i + i * y.r); }
    Complex operator *=(const Complex &y) {
        double t = r;
        return Complex(r = r * y.r - i * y.i, i = t * y.i + i * y.r); }
}
a[MAXN], b[MAXN];
double Pi=acos(-1);
void FFT(Complex* a,long len,int op){
    
    if(len==1)
        return;
    Complex * a0=new Complex[len/2];
    Complex * a1=new Complex[len/2];
    for(long i=0;i<len;i+=2){
        a0[i/2]=a[i];
        a1[i/2]=a[i+1];
    }
    
    FFT(a0,len/2,op);
    FFT(a1,len/2,op);
    Complex wn(cos(2*Pi/len),op*sin(2*Pi/len));
    Complex w(1,0);
    
    for(long i=0;i<(len/2);i++){
        a[i]=a0[i]+w*a1[i];
        a[i+len/2]=a0[i]-w*a1[i];
        w=w*wn;
        
    }
    
    delete[] a0;
    delete[] a1;
}

int main(int argc, const char * argv[]) {
    clock_t start, finish;
    float duration;
    
    int ordP1,ordP2,len;
    double innc;
    Complex Poly1[100],Poly2[100],Poly3[100];
    printf("the max power of the polynomial : ");
    scanf("%d",&ordP1);
    printf("coefficient of the polynomial 1:(from x^n to x^0) ");
    
    for(int i=0;i<=ordP1;i++){
        scanf("%lf",&innc);
        Poly1[i].r=innc;
        Poly1[i].i=0;
    }
    std::cout << Poly1[1].r;
    printf("the max power of the polynomial 2: ");
    scanf("%d",&ordP2);
    printf("coefficient of the polynomial 2:(from x^n to x^) ");
    for(int i=0;i<=ordP2;i++){
        scanf("%lf",&innc);
        Poly2[i].r=innc;
        Poly2[i].i=0.0;
    }
    start = clock();
    for(int i=1; i<=abs(ordP1-ordP2) && (ordP1-ordP2!=0) ;i++){
        
        if(ordP1-ordP2<0){
            Poly1[i+ordP1]*=Complex(0.0,0.0);
            
        }else{
            Poly2[i+ordP2]*=Complex(0.0,0.0);
        }
    }
    
    len = (ordP1-ordP2)?(ordP1+1):(ordP2+1);
    
    for(len = 2; len < ordP1+ordP2+2;len*=2);
    
    std::cout<<len<<"\\\\"<<'\n';
    for(int i =ordP1+1;i<len;i++){
        Poly1[i] = Poly1[i] * Complex(0.0,0.0);
        Poly2[i] = Poly2[i] * Complex(0.0,0.0);
    }
    
    
    FFT(Poly1,len,1);
    FFT(Poly2,len,1);
    
    for (int i =0;i<len;i++){
        Poly3[i]=Poly1[i]*Poly2[i];
    }
    
    FFT(Poly3,len,-1);
    for (int i =0;i<len;i++){
        Poly3[i].r /= len;
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
    for(int i = 0;i< ordP1+ordP2+1 ;i++)
        
        printf("%lf ",Poly3[i].r);
    printf("\n");
    return 0;
}
