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

StringSet RandomStringGenerator::generateStringSet(ulong stringLength, ulong numStrings) {
    StringSet set(stringLength, numStrings);
    fillStringSet(set);
    return set;
}
void RandomStringGenerator::fillStringSet(StringSet &set) {
    char** data = set.getData();
    for (ulong str = 0; str < set.getNumStrings(); ++str) {
        for (ulong letter = 0; letter < set.getStringLength(); ++letter) {
            data[str][letter] = alphabet[uni(rng)];
        }
    }
}
