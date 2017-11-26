//
// Created by michal on 25.11.17.
//

#include "RandomStringGenerator.h"



RandomStringGenerator::RandomStringGenerator() : uni(0, 2) {
    std::random_device rd;
    rng.seed(rd());
    alphabet[0] = '0';
    alphabet[1] = '1';
    alphabet[2] = '*';
}

StringSet RandomStringGenerator::generateStringSet(int stringLength, int numStrings) {
    auto** data = new char* [numStrings];
    for (int i = 0; i < numStrings; ++i) {
        data[i] = new char[stringLength];
    }

    for (int str = 0; str < numStrings; ++str) {
        for (int letter = 0; letter < stringLength; ++letter) {
            data[str][letter] = alphabet[uni(rng)];
        }
    }

    return StringSet(data, stringLength, numStrings);
}