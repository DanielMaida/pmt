#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glob.h>
#include <vector>

#include "kmp.h"

using namespace std;

std::vector<std::string> glob(const std::string& pat){
    glob_t glob_result;
    glob(pat.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> ret;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        ret.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return ret;
}

int main (int argc, char **argv)
{
  int c;
  int countFlag = 0;
  int helpFlag = 0;
  char const *editArgument = "";
  char const *algorithmArgument = "";
  char const *pattern = "";
  char const *patternFilePath = "";
  char const *filePath = "";

  while (1)
    {
      static struct option long_options[] =
        {
          {"count",  no_argument, 0, 'c'},
          {"help",  no_argument,       0, 'h'},
          {"edit",    required_argument, 0, 'e'},
          {"algorithm",     required_argument,0, 'a'},
          {"pattern",  required_argument, 0, 'p'}          
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "che:a:p:",
                       long_options, &option_index);

      if (c == -1 || helpFlag == 1)
        break;

      switch (c)
        {
        case 'c':
          countFlag = 1;
          break;

        case 'h':
          helpFlag = 1;
          break;

        case 'e':
          editArgument = optarg;
          break;

        case 'a':
          algorithmArgument = optarg;
          break;

        case 'p':
          patternFilePath = optarg;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }
    
  if(!helpFlag)
    {
      if(strcmp(patternFilePath,"")!=0 && argc - optind == 1)
        {          
          //espera um argumento          
          filePath = argv[optind++];       
        }
      else if(argc - optind == 2)
        {
          //esperando dois argumentos    
          pattern = argv[optind++];
          filePath = argv[optind++];
        }
      else
        {
          //throw error or something
          helpFlag = 1;
        }       
    }
  
  if(helpFlag)
    {
      printf("Usage: pmt [OPTION] PATTERN FILE\n"
             "Example: pmt -c church shakespeare.txt\n\n"
             "Options:\n"
             "  -c, --count                     print only the total ammount of matches of the pattern(s) in the FILE(s)\n"
             "  -e, --edit=MAX_DIST             MAX_DIST is the max distance from the pattern(s) that will be considered when searched\n"
             "  -a, --algorithm=ALGORITHM       use the chosen ALGORITHM instead of the default one. ALGORITHM can be one of the following: kmp, sellers\n"
             "  -p, --pattern=PATTERNFILE       PATTERNFILE is the filepath of the file that contains the patterns to be searched\n");
    }
  else
    {
      std::vector<std::string> files = glob(filePath);
      //call algorithms
      if(strcmp(algorithmArgument,"")!=0)
        {
          //algorithm was chosen
          if(strcmp(algorithmArgument, "kmp")==0)
            {
              //call kmp
              printf("found %d occurrences\n", callKmp((strcmp(patternFilePath,"")!=0)?patternFilePath:pattern,
                                                      files,
                                                      (strcmp(patternFilePath,"")),
                                                      countFlag
                                                      ));
              
            }
          else if(strcmp(algorithmArgument, "sellers")==0)
            {
              //call sellers
                        
            }
          else
            {
              printf("choose one of the following algorithms: kmp, sellers \ncall kmp -h if you need more information\n");
            }
        }
      else
        {
          //call algorithms based on something
          if(strcmp(editArgument,"")!=0)
            {
              //call sellers
                         
            }
          else
            {
              //call kmp
              printf("found %d occurrences\n", callKmp((strcmp(patternFilePath,"")!=0)?patternFilePath:pattern,
                                                      files,
                                                      (strcmp(patternFilePath,"")),
                                                      countFlag
                                                      ));              
            }         
        }
    }
   
  exit (0);
}


