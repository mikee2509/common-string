//
// Created by michal on 12.11.17.
//

#ifndef AAL_STRINGSET_H
#define AAL_STRINGSET_H

#include <cmath>
#include <vector>
#include <ostream>
#include "../DataTypes.h"

class StringSet {
    char* buffer = nullptr;
    char** data = nullptr;
    ulong stringLength;
    ulong numStrings;

public:
    StringSet(ulong stringLength, ulong numStrings);
    virtual ~StringSet();
    char** getData() const;
    ulong getStringLength() const;
    ulong getNumStrings() const;
    friend std::ostream &operator<<(std::ostream &os, const StringSet &set);
};

#endif //AAL_STRINGSET_H
