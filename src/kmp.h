#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int callKmp(std::string pattern, std::vector<std::string> textFiles, int patternIsPatternPath, int printOnlyCount);

#endif
