/*************************************************************************
    > File Name: sequences_combination.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 04 Oct 2016 12:38:07 PM
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/*
 * problem:
 * given two sequences of positive integers a_1 ~ a_n and b_1 ~ b_n
 * where all numbers are less than n^2
 * given a positive integer B, such that B<=n^3
 * problem is to determine if there is a sequence c_1 ~ c_n, such that
 * sum(c_i)=B where i=1,2,...,n and c_i=a_i or b_i in polynomial time
 *
 * solution: http://www.csc.kth.se/utbildning/kth/kurser/DD2354/algokomp10/Ovningar/Exercise3+4_Sol.pdf
*/

bool CheckSeqCombinations(int B, const vector<int>& a, const vector<int>& b){
    int n = a.size();

    vector<vector<bool>> F;

    for(int j=0;j<n;j++){
        vector<bool> vecTemp;
        F.push_back(vecTemp);
        for(int s=0;s<=B;s++){
            F[j].push_back(false);
            if(j==0 && s==0) F[j][s] = true;
        }
    }

    for(int j=1;j<n;j++){
        for(int s=1;s<=B;s++){
            F[j][s] = F[j-1][s-a[j]] || F[j-1][s-b[j]]; 
        }
    }

    return F[n][B];
}

