//
// Created by michal on 25.11.17.
//

#ifndef AAL_RANDOMSTRINGGENERATOR_H
#define AAL_RANDOMSTRINGGENERATOR_H

#include <random>
#include "../data/StringSet.h"

class RandomStringGenerator {
    std::uniform_int_distribution<int> uni;
    std::mt19937 rng;    // Mersenne-Twister random-number engine
    char alphabet[3];

public:
    RandomStringGenerator();
    StringSet generateStringSet(int stringLength, int numStrings);

};

#endif //AAL_RANDOMSTRINGGENERATOR_H
