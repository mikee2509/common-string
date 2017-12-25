//
// Created by michal on 26.11.17.
//

#ifndef AAL_COMMONSTRINGFINDER_H
#define AAL_COMMONSTRINGFINDER_H

#include "../data/StringSet.h"
#include <string>
#include <list>
#include <algorithm>

class CommonStringFinder {
    char* key;
    int stringLength;
    int numStrings;
    void incrementKey();
public:
    std::string bruteForce(StringSet &set);
    std::string heuristic(StringSet &set);
private:
    bool changeKey(StringSet &set, int currentStrIndex, std::list<int>* matchingStrings, int* matchingLetters);
    void deallocate(const std::list<int>* matchingStrings, const int* matchingLetters);
};

#endif //AAL_COMMONSTRINGFINDER_H
