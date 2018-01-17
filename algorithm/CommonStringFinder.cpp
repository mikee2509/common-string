//
// Created by michal on 26.11.17.
//

#include "CommonStringFinder.h"

using namespace std;

CommonStringFinder::Result CommonStringFinder::bruteForce(const StringSet &set) {
    ulong stringLength = set.getStringLength();
    ulong numStrings = set.getNumStrings();
    char** data = set.getData();

    char key[stringLength];
    for (ulong i = 0; i < stringLength; ++i) {
        key[i] = '0';
    }
    ulong keyChanges = 0;
    double numCombinations = pow(2, stringLength);

    for (long long combination = 0; combination < numCombinations; ++combination) {
        bool keyMatches = checkKey(stringLength, numStrings, key, data);
        if (keyMatches) {
            return Result(SOLUTION, keyChanges, string(key, stringLength));
        }
        incrementKey(key, stringLength);
        ++keyChanges;
    }

    return Result(NO_SOLUTION, keyChanges);
}

bool CommonStringFinder::checkKey(ulong &stringLength, ulong &numStrings, const char* key, char* const* data) {
    for (ulong str = 0; str < numStrings; ++str) {
        bool match = false;
        for (ulong letter = 0; letter < stringLength; ++letter) {
            if (data[str][letter] == key[letter]) {
                match = true;
                break;
            }
        }
        if (!match) {
            return false;
        }
    }
    return true;
}

void CommonStringFinder::incrementKey(char* key, const ulong &length) {
    for (ulong i = 0; i < length; ++i) {
        if (key[i] == '0') {
            key[i] = '1';
            break;
        }
        key[i] = '0';
    }
}

CommonStringFinder::Result CommonStringFinder::heuristic(const StringSet &set) {
    ulong stringLength = set.getStringLength();
    ulong numStrings = set.getNumStrings();

    char key[stringLength];
    char** data = set.getData();

    // For each letter in key hold indices of Strings matching at that position 
    list<ulong> matchingStrings[stringLength];

    // For each String hold the number of letters which match with current key
    ulong matchingLetters[numStrings] = {0};

    // Initialize key to first string with *s replaced by 0s
    for (ulong i = 0; i < stringLength; ++i) {
        if (data[0][i] == '*') {
            key[i] = '0';
        } else {
            key[i] = data[0][i];
        }
    }

    ulong keyChanges = 0;
    for (ulong str = 0; str < numStrings; ++str) {
        vector<ulong> changeablePositions;
        for (ulong letter = 0; letter < stringLength; ++letter) {
            if (data[str][letter] == key[letter]) {
                matchingLetters[str] += 1;
                matchingStrings[letter].push_back(str);
            }
            if (data[str][letter] != '*') {
                changeablePositions.push_back(letter);
            }
        }
        if (changeablePositions.empty()) {
            return Result(NO_SOLUTION, keyChanges);
        }
        if (matchingLetters[str] == 0) {
            if (!changeKey(key, set, str, matchingStrings, matchingLetters, changeablePositions)) {
                return Result(SOLUTION_NOT_FOUND, keyChanges);
            }
            ++keyChanges;
        }
    }

    return Result(SOLUTION, keyChanges, string(key, stringLength));
}

// Pair of matchingStrings array index and pointer to corresponding matchingStrings array element
typedef pair<ulong, list<ulong>*> myPair;

bool CommonStringFinder::changeKey(char* key,
                                   const StringSet &set,
                                   ulong currentStrIndex,
                                   list<ulong>* matchingStrings,
                                   ulong* matchingLetters,
                                   vector<ulong> &changeablePositions) {
    list<myPair> myPairList;
    for (ulong &position : changeablePositions) {
        myPairList.emplace_back(position, &matchingStrings[position]);
    }

    ulong keyIndexToChange = 0;
    bool indexToChangeFound = false;

    // For each changeable letter in key
    while (!myPairList.empty()) {
        // Find the one having the least matchingStrings
        auto pairIterator = min_element(myPairList.begin(),
                                        myPairList.end(),
                                        [](myPair &lhs, myPair &rhs) {
                                            return lhs.second->size() < rhs.second->size();
                                        });
        myPair &pair = *pairIterator;
        list<ulong> &pList = *pair.second;
        ulong &keyIndex = pair.first;

        // Is it safe to change key letter at this keyIndex
        bool isSafe = true;

        // For each matchingString
        for (ulong &stringIndex : pList) {
            // If the number of matching letters is less than two (TODO change to equals 1)
            if (matchingLetters[stringIndex] < 2) {
                isSafe = false;
                break;
            }
        }

        if (isSafe) {
            keyIndexToChange = keyIndex;
            indexToChangeFound = true;
            break;
        }

        myPairList.erase(pairIterator);
    }

    if (!indexToChangeFound) {
        return false;
    }

    char oldKeyLetter = key[keyIndexToChange];
    char newKeyLetter = oldKeyLetter == '0' ? '1' : '0';
    key[keyIndexToChange] = newKeyLetter;
    char** data = set.getData();

    for (ulong str = 0; str < currentStrIndex + 1; ++str) {
        if (data[str][keyIndexToChange] == newKeyLetter) {
            matchingLetters[str] += 1;
            matchingStrings[keyIndexToChange].push_back(str);
        } else if (data[str][keyIndexToChange] == oldKeyLetter) {
            matchingLetters[str] -= 1;
            matchingStrings[keyIndexToChange].remove(str);
        }
    }

    return true;
}

CommonStringFinder::Result CommonStringFinder::heuristicInteractive(const StringSet &set,
                                                                    const function<void(const char* key,
                                                                                        const StringSet &set,
                                                                                        const ulong* matchingLetters,
                                                                                        const list<ulong>* matchingStrings,
                                                                                        ulong currentStrIndex,
                                                                                        bool keyChanged)> &peekFunction) {
    ulong stringLength = set.getStringLength();
    ulong numStrings = set.getNumStrings();

    char key[stringLength];
    char** data = set.getData();

    // For each letter in key hold indices of Strings matching at that position
    list<ulong> matchingStrings[stringLength];

    // For each String hold the number of letters which match with current key
    ulong matchingLetters[numStrings] = {0};

    // Initialize key to first string with *s replaced by 0s
    for (ulong i = 0; i < stringLength; ++i) {
        if (data[0][i] == '*') {
            key[i] = '0';
        } else {
            key[i] = data[0][i];
        }
    }

    ulong keyChanges = 0;
    for (ulong str = 0; str < numStrings; ++str) {
        vector<ulong> changeablePositions;
        for (ulong letter = 0; letter < stringLength; ++letter) {
            if (data[str][letter] == key[letter]) {
                matchingLetters[str] += 1;
                matchingStrings[letter].push_back(str);
            }
            if (data[str][letter] != '*') {
                changeablePositions.push_back(letter);
            }
        }
        if (peekFunction != nullptr) {
            peekFunction(key, set, matchingLetters, matchingStrings, str, false);
        }
        if (changeablePositions.empty()) {
            return Result(NO_SOLUTION, keyChanges);
        }
        if (matchingLetters[str] == 0) {
            if (!changeKey(key, set, str, matchingStrings, matchingLetters, changeablePositions)) {
                return Result(SOLUTION_NOT_FOUND, keyChanges);
            }
            if (peekFunction != nullptr) {
                peekFunction(key, set, matchingLetters, matchingStrings, str, true);
            }
            ++keyChanges;
        }
    }

    return Result(SOLUTION, keyChanges, string(key, stringLength));
}

ostream &operator<<(ostream &os, const CommonStringFinder::Result &result) {
    switch (result.type) {
        case CommonStringFinder::SOLUTION:
            if (result.value.length() > 20) {
                os << result.value.substr(0, 20) + "(...)";
            } else {
                os << result.value;
            }
            break;
        case CommonStringFinder::NO_SOLUTION:
            os << "Solution doesn't exist";
            break;
        case CommonStringFinder::SOLUTION_NOT_FOUND:
            os << "Solution not found";
    }
    return os;
}
bool CommonStringFinder::Result::solutionFound() const {
    return type == SOLUTION;
}

bool CommonStringFinder::doesKeyMatch(std::string &key, StringSet &set) {
    ulong stringLength = set.getStringLength();
    ulong numStrings = set.getNumStrings();
    return checkKey(stringLength, numStrings, key.c_str(), set.getData());
}
