//
//  main.cpp
//  5-2-2
//
//  Created by lu juihung on 2/16/18.
//  Copyright © 2018 lu juihung. All rights reserved.
//

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;

void karatsuba(ll *res, const ll *p, const ll *q, int sz){
    ll t0[sz], t1[sz], r[sz<<1];
    
    memset(r, 0, (sz<<1) * sizeof(ll));
    
    if ( sz <= 4 ){ 
        for ( int i = 0 ; i < sz ; i++ )
            for ( int j = 0 ; j < sz ; j++ ){
                r[i + j] += p[i] * q[j];
            }
    } else {

        int nSz = (sz >> 1);
        
        for ( int i = 0 ; i < nSz ; i++ ){
            t0[i] = p[i] + p[nSz + i];
            t1[i] = q[i] + q[nSz + i];
            t0[i + nSz] = t1[i + nSz] = 0;
        }
        
        karatsuba(r + nSz, t0, t1, nSz);
        karatsuba(t0, p, q, nSz);
        karatsuba(t1, p + nSz, q + nSz, nSz);
        
        for ( int i = 0 ; i < sz ; i++ ){
            r[i] += t0[i];
            r[i + nSz] -= t0[i] + t1[i];
            r[i + sz] += t1[i];
        }
    }
    
    memcpy(res, r, (sz<<1) * sizeof(ll));
}

void polyMult(ll *r, ll *p, ll *q, int sz){
    if ( sz & (sz - 1) ){ // if size is not power of two
        int k = 1;
        while ( k < sz ) k <<= 1;
        while ( ++sz <= k ) p[sz - 1] = q[sz - 1] = 0;
        sz--;
    }
    
    karatsuba(r, p, q, sz);
}

// print polynomial in descending order of degree
void polyPrint(ll *p, int sz){
    while ( --sz >= 0 ) cout << p[sz] <<" ";
    puts("");
}

int main(){
    ll p[4] = {1,3,3,1};
    ll q[4] = {-1,3,-3,1};
    ll r[8];
    int degree = 3;
    
    polyMult(r, p, q, degree + 1);
    polyPrint(r, degree * 2 + 1);
    return 0;
}
