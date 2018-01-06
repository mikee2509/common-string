//
// Created by michal on 26.11.17.
//

#ifndef AAL_COMMONSTRINGFINDER_H
#define AAL_COMMONSTRINGFINDER_H

#include "../data/StringSet.h"
#include "../DataTypes.h"
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <utility>
#include <ostream>

class CommonStringFinder {
public:
    enum ResultType {
        SOLUTION,          // Solution found
        NO_SOLUTION,       // Solution doesn't exist
        SOLUTION_NOT_FOUND // Solution hasn't been found but it may exist
    };

    struct Result {
        ResultType type;
        std::string value;
        explicit Result(ResultType type) : type(type) {}
        Result(ResultType type, std::string value) : type(type), value(std::move(value)) {}
        friend std::ostream &operator<<(std::ostream &os, const Result &result);
    };

    Result bruteForce(StringSet &set);
    Result heuristic(StringSet &set);
    Result heuristicInteractive(StringSet &set,
                                const std::function<void(const char* key,
                                                         const StringSet &set,
                                                         const ulong* matchingLetters,
                                                         const std::list<ulong>* matchingStrings,
                                                         ulong currentStrIndex,
                                                         bool keyChanged)> &peekFunction = nullptr);

private:
    void incrementKey(char* key, const ulong &length);
    bool changeKey(char* key,
                   StringSet &set,
                   ulong currentStrIndex,
                   std::list<ulong>* matchingStrings,
                   ulong* matchingLetters,
                   std::vector<ulong> &changeablePositions);
};

#endif //AAL_COMMONSTRINGFINDER_H