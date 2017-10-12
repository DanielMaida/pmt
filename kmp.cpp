#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <int> preTable(1000);


void createTable(string pattern) {
    int j = 0;
    int i = j + 1;
    preTable[j] = 0;
    while (i < pattern.length()) {
        if(pattern[i] != pattern[j]) {
            if(j == 0) {
                preTable[i] = 0;
                i++;
            } else {
                j = preTable[j - 1];
            }
        } else {
            preTable[i] = j + 1;
            j++;
            i++;
        }
    }
}

int kmp(string text, string pattern) {
    int occ = 0;
    createTable(pattern);
    int i = 0; //text index
    int j = 0; //border index
    while( i < text.length()) {
        if(text[i] == pattern[j]) {
            if(j == pattern.length() - 1) {
                occ++; 
                i++;
                j = 0;
            } else {
                i++; j++;
            }
        } else {
            if (j > 0)
                j = preTable[j - 1];
            else
                i++;
        }
    }
    return occ;
}

int main(){
    
    string text = "abxabcabcabyabc";
    string pattern = "abc";

    int occ = kmp(text, pattern);
    cout << occ << endl;
    return 0;
}