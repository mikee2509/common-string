//
// Created by michal on 12.11.17.
//

#ifndef AAL_STRINGSET_H
#define AAL_STRINGSET_H

#include <cmath>
#include <vector>

class StringSet {
    char* buffer = nullptr;
    char** data = nullptr;
    int stringLength;
    int numStrings;

public:
    StringSet(int stringLength, int numStrings);
    virtual ~StringSet();
    char** getData() const;
    int getStringLength() const;
    int getNumStrings() const;

};

#endif //AAL_STRINGSET_H
