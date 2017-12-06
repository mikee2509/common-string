//
// Created by michal on 26.11.17.
//

#include <algorithm>
#include "CommonStringFinder.h"

using namespace std;

string CommonStringFinder::bruteForce(StringSet &set) {
    stringLength = set.getStringLength();
    key = new char[stringLength];
    for (int i = 0; i < stringLength; ++i) {
        key[i] = '0';
    }

    char** data = set.getData();

    double numCombinations = pow(2, stringLength);
    //for each key
    for (long long combination = 0; combination < numCombinations; ++combination) {
        //should next key be checked
        bool nextKey = false;
        //for each string in set
        for (int str = 0; str < set.getNumStrings(); ++str) {
            //does current key match string?
            bool match = false;
            //for each letter
            for (int letter = 0; letter < stringLength; ++letter) {
                //check if at least one of them matches
                if (data[str][letter] == key[letter]) {
                    match = true;
                    break;
                }
            }
            //if not a single letter match check with next key
            if (!match) {
                nextKey = true;
                break;
            }
        }
        if (!nextKey) {
            const string &result = string(key);
            delete[] key;
            key = nullptr;
            return result;
        }
        incrementKey();
    }

    delete[] key;
    key = nullptr;
    return string("No match");
}

void CommonStringFinder::incrementKey() {
    for (int i = 0; i < stringLength; ++i) {
        if (key[i] == '0') {
            key[i] = '1';
            break;
        }
        key[i] = '0';
    }
}

std::string CommonStringFinder::heuristic(StringSet &set) {
    stringLength = set.getStringLength();
    numStrings = set.getNumStrings();

    key = new char[stringLength]; //TODO delete
    char** data = set.getData();

    // For each letter in key hold indices of Strings matching at that position 
    auto* matchingStrings = new vector<int>[stringLength]; //TODO deallocate

    // For each String hold the number of letters which match with current key
    auto* matchingLetters = new int[numStrings]; //TODO deallocate

    // Initialize key to first string with *s replaced by 0s
    for (int i = 0; i < stringLength; ++i) {
        if (data[0][i] == '*') {
            key[i] = '0';
        } else {
            key[i] = data[0][i];
        }
    }

    for (int str = 0; str < numStrings; ++str) {
        for (int letter = 0; letter < stringLength; ++letter) {
            if (data[str][letter] == key[letter]) {
                matchingLetters[str] += 1;
                matchingStrings[letter].push_back(str);
            }
        }
        if (matchingLetters[str] == 0) {
            bool result = changeKey(str, matchingStrings, matchingLetters);
            //TODO handle result
        }
    }

}

bool compareByVecSize(pair<int, vector<int>*> &lhs, pair<int, vector<int>*> &rhs) {
    return lhs.second->size() < rhs.second->size();
}

bool CommonStringFinder::changeKey(int currentStrIndex, vector<int>* matchingStrings, int* matchingLetters) {
    // Pair of matchingStrings array index and pointer to corresponding matchingStrings array element
    typedef pair<int, vector<int>*> myPair;

    vector<myPair> myVec;
    myVec.reserve(static_cast<unsigned long>(stringLength));
    for (int i = 0; i < stringLength; ++i) {
        myVec.emplace_back(i, &matchingStrings[i]);
    }

    sort(myVec.begin(),
         myVec.end(),
         [](myPair &lhs, myPair &rhs) { return lhs.second->size() < rhs.second->size(); });

    int keyIndexToChange = -1;

    // For each letter in key starting with the one having the least matchingStrings
    for (auto &pair : myVec) {

        vector<int> &pVec = *pair.second;
        int &keyIndex = pair.first;

        // Is it safe to change key letter at this keyIndex
        bool isSafe = true;

        // For each matchingString
        for (int &stringIndex : pVec) {
            // If the number of matching letters is less than two (TODO change to equals 1)
            if (matchingLetters[stringIndex] < 2) {
                isSafe = false;
                break;
            }
        }

        if (isSafe) {
            keyIndexToChange = keyIndex;
            break;
        }
    }

    if (keyIndexToChange == -1) {
        return false;
    }

    //TODO change key
    //TODO increment matchingLetters counts
    //TODO update matchingStrings vectors
}


