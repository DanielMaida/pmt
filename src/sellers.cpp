#include "sellers.h"

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

int callSellersForEachFile (string pattern, std::vector<std::string> textFiles,int printOnlyCount, int error)
{
  int totalOccurrencesInFile = 0;
       
  for(std::vector<string>::iterator it = textFiles.begin(); it != textFiles.end(); ++it)
  {    
    std::string textPath = *it;
    std::ifstream textFile(textPath.c_str());
    if(textFile.is_open())
    {
      for(string textLine; getline(textFile, textLine);)
      {
        int lineOccurrences = 0;
        lineOccurrences += sellers(textLine, pattern,error);
        if(lineOccurrences > 0 && printOnlyCount != 1)
        {
          printf("%s\n", textLine.c_str());
        }
        totalOccurrencesInFile += lineOccurrences;                 
      }
    }
  }
  return totalOccurrencesInFile;    
}

int callSellers(string pattern, std::vector<std::string> textFiles, int patternIsPatternPath, int printOnlyCount, int error)
{
  int totalOccurrences = 0;
  
  if(patternIsPatternPath!=0)
  {
    std::ifstream patternFile(pattern.c_str());             
    if(patternFile.is_open())
    {    
      for(std::string patternLine; getline(patternFile,patternLine);)
      {
        totalOccurrences += callSellersForEachFile(patternLine, textFiles, printOnlyCount, error);                                                             
      }          
    }  
  }
  else
  {
    totalOccurrences = callSellersForEachFile(pattern, textFiles,printOnlyCount,error);              
  }
  return totalOccurrences;
}
