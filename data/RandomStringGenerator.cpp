//
// Created by michal on 25.11.17.
//

#include "RandomStringGenerator.h"

RandomStringGenerator::RandomStringGenerator() : uni(0, 2) {
//    std::random_device rd;
    rng.seed(1);
    alphabet[0] = '0';
    alphabet[1] = '1';
    alphabet[2] = '*';
}

StringSet RandomStringGenerator::generateStringSet(ulong stringLength, ulong numStrings) {
    StringSet set(stringLength, numStrings);
    char** data = set.getData();
    for (ulong str = 0; str < numStrings; ++str) {
        for (ulong letter = 0; letter < stringLength; ++letter) {
            data[str][letter] = alphabet[uni(rng)];
        }
    }

    return set;
}
