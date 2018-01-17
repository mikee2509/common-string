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
        ulong keyChanges = 0;
        std::string value;
        Result() : type(SOLUTION_NOT_FOUND) {}
        Result(ResultType type, ulong keyChanges) : type(type), keyChanges(keyChanges) {}
        Result(ResultType type, ulong keyChanges, std::string value)
                : type(type), keyChanges(keyChanges), value(std::move(value)) {}
        friend std::ostream &operator<<(std::ostream &os, const Result &result);
        bool solutionFound() const;
    };

    bool doesKeyMatch(std::string &key, StringSet &set);
    Result bruteForce(StringSet &set);
    Result heuristic(StringSet &set);
    Result heuristicInteractive(StringSet &set,
                                const std::function<void(const char* key,
                                                         const StringSet &set,
                                                         const ulong* matchingLetters,
                                                         const std::vector<ulong>* matchingStrings,
                                                         ulong currentStrIndex,
                                                         bool keyChanged)> &peekFunction = nullptr);

private:
    bool checkKey(ulong &stringLength, ulong &numStrings, const char* key, char* const* data);
    void incrementKey(char* key, const ulong &length);
    bool changeKey(char* key,
                   StringSet &set,
                   ulong currentStrIndex,
                   std::vector<ulong>* matchingStrings,
                   ulong* matchingLetters,
                   std::vector<ulong> &changeablePositions);
};

#endif //AAL_COMMONSTRINGFINDER_H