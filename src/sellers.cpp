#include <iostream>
#include <string>

using namespace std;

int * newCol(int *col, string pat, char a){
     int m = pat.length();
     int * ncol = new int[m+1]; ncol[0] = 0;
     for (int i = 1; i < m+1; i++){
        int phi = 1;
        if( a == pat[i-1])
            phi = 0;
            ncol[i] = min(min(col[i]+1, ncol[i-1]+1), col[i-1]+phi);
    }
    return ncol;
}

int sellers(string text, string pat, int error){
    int n = text.length();
    int m = pat.length();
    int * col = new int[m+1];
    int occ = 0;
    for(int i = 0; i < m+1; i++){
        col[i] = i;
    }
    for(int j = 0; j < n; j++){
        col = newCol(col,pat,text[j]);
        if(col[m] <= error){
            occ++;
        }
    }
    return occ;
}
