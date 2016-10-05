/*************************************************************************
    > File Name: matrix_multiplication.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Wed 05 Oct 2016 04:58:51 PM
 ************************************************************************/

#include<iostream>
using namespace std;

#define N 100
#define M 150

int A[N][M];
int B[M][N];
int C[N][N];

/*
 * how to compute do matrix multiplications?
 * for example, given a NxM matrix A and a MxN matrix B
 * after multiplication, we can get a NxN matrix C
 * since C has N^2 elements
 * we need to compute each element individually
 * and each element C[i][j] is obtained by sum(A[i][k] * B[k][j]),k=1~m, and each element takes O(n) time 
 * time complexity is O(N^3)
*/

void matrix_multiply(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<M;k++) C[i][j]+=A[i][k]*B[k][j];
        }
    }
}

