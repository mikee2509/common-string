//
// Created by michal on 25.11.17.
//

#ifndef AAL_RANDOMSTRINGGENERATOR_H
#define AAL_RANDOMSTRINGGENERATOR_H

#include <random>
#include "StringSet.h"
#include "../DataTypes.h"

class RandomStringGenerator {
    std::uniform_int_distribution<int> uni;
    std::mt19937 rng;    // Mersenne-Twister random-number engine
    char alphabet[3];

public:
    RandomStringGenerator();
    StringSet generateStringSet(ulong stringLength, ulong numStrings);
    void fillStringSet(StringSet& set);

};

#endif //AAL_RANDOMSTRINGGENERATOR_H
