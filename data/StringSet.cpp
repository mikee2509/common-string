//
// Created by michal on 12.11.17.
//

#include "StringSet.h"

StringSet::StringSet(int stringLength, int numStrings)
        : stringLength(stringLength), numStrings(numStrings) {

    // One contiguous memory block
    buffer = new char[numStrings * stringLength];
    data = new char* [numStrings];
    for (int i = 0; i < numStrings; ++i) {
        data[i] = &buffer[i*stringLength];
    }

    // Many small chunks of memory
//    data = new char* [numStrings];
//    for (int i = 0; i < numStrings; ++i) {
//        data[i] = new char[stringLength];
//    }

}

StringSet::~StringSet() {
    delete[] buffer;
    delete[] data;

//    for (int i = 0; i < numStrings; ++i) {
//        delete[] data[i];
//    }
//    delete[] data;
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
