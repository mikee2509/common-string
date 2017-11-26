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
    void incrementKey();
public:
    std::string find(StringSet &set);
};

#endif //AAL_COMMONSTRINGFINDER_H
