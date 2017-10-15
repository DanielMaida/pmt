#include "kmp.h"

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

int callKmpForEachFile (string pattern, std::vector<std::string> textFiles,int printOnlyCount)
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
        lineOccurrences += kmp(textLine, pattern);
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

int callKmp(string pattern, std::vector<std::string> textFiles, int patternIsPatternPath, int printOnlyCount)
{
  int totalOccurrences = 0;
  
  if(patternIsPatternPath!=0)
  {
    std::ifstream patternFile(pattern.c_str());             
    if(patternFile.is_open())
    {    
      for(std::string patternLine; getline(patternFile,patternLine);)
      {
        totalOccurrences += callKmpForEachFile(patternLine, textFiles, printOnlyCount);                                                             
      }          
    }  
  }
  else
  {
    totalOccurrences = callKmpForEachFile(pattern, textFiles,printOnlyCount);              
  }
  return totalOccurrences;
}

