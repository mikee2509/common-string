//
// Created by michal on 26.11.17.
//

#ifndef AAL_COMMONSTRINGFINDER_H
#define AAL_COMMONSTRINGFINDER_H

#include "../data/StringSet.h"
#include <string>

class CommonStringFinder {
    char* key;
    int stringLength;
    int numStrings;
    void incrementKey();
public:
    std::string bruteForce(StringSet &set);
    std::string heuristic(StringSet &set);
    bool changeKey(int i, std::vector<int>* matchingStrings, int* matchingLetters);
};

#endif //AAL_COMMONSTRINGFINDER_H
