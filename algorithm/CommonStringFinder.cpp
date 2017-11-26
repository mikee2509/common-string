//
// Created by michal on 26.11.17.
//

#include "CommonStringFinder.h"
#include <cmath>

using namespace std;

string CommonStringFinder::find(StringSet &set) {
    stringLength = set.getStringLength();
    key = new char[stringLength];
    for (int i = 0; i < stringLength; ++i) {
        key[i] = '0';
    }

    char** data = set.getData();

    //for each key
    for (long long combination = 0; combination < pow(2, stringLength); ++combination) {
        //should next key be checked
        bool nextKey = false;
        //for each string in set
        for (int string = 0; string < set.getNumStrings(); ++string) {
            //does current key match string?
            bool match = false;
            //for each letter
            for (int letter = 0; letter < stringLength; ++letter) {
                //check if at least one of them matches
                if (data[string][letter] == key[letter]) {
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
            return string(key);
        }
        incrementKey();
    }

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


