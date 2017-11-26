//
// Created by michal on 12.11.17.
//

#include "StringSet.h"

StringSet::StringSet() = default;

StringSet::StringSet(char** data, int stringLength, int numStrings)
        : data(data), stringLength(stringLength), numStrings(numStrings) {}

StringSet::~StringSet() {
    for (int i = 0; i < numStrings; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

char** StringSet::getData() const {
    return data;
}

int StringSet::getStringLength() const {
    return stringLength;
}

int StringSet::getNumStrings() const {
    return numStrings;
}
