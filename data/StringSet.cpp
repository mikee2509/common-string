//
// Created by michal on 12.11.17.
//

#include "StringSet.h"

StringSet::StringSet(ulong stringLength, ulong numStrings)
        : stringLength(stringLength), numStrings(numStrings) {

    // One contiguous memory block
    buffer = new char[numStrings * stringLength];
    data = new char* [numStrings];
    for (ulong i = 0; i < numStrings; ++i) {
        data[i] = &buffer[i*stringLength];
    }

    // Many small chunks of memory
//    data = new char* [numStrings];
//    for (ulong i = 0; i < numStrings; ++i) {
//        data[i] = new char[stringLength];
//    }

}

StringSet::~StringSet() {
    delete[] buffer;
    delete[] data;

//    for (ulong i = 0; i < numStrings; ++i) {
//        delete[] data[i];
//    }
//    delete[] data;
}

char** StringSet::getData() const {
    return data;
}

ulong StringSet::getStringLength() const {
    return stringLength;
}

ulong StringSet::getNumStrings() const {
    return numStrings;
}

std::ostream &operator<<(std::ostream &os, const StringSet &set) {
    for (ulong i = 0; i < set.numStrings; ++i) {
        for (ulong j = 0; j < set.stringLength; ++j) {
            os << set.data[i][j];
        }
        os << std::endl;
    }
    return os;
}
