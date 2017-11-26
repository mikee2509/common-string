//
// Created by michal on 12.11.17.
//

#ifndef AAL_STRINGSET_H
#define AAL_STRINGSET_H

class StringSet {
    char** data = nullptr;
    int stringLength;
    int numStrings;

public:
    StringSet();
    StringSet(char** data, int stringLength, int numStrings);
    virtual ~StringSet();
    char** getData() const;
    int getStringLength() const;
    int getNumStrings() const;

};

#endif //AAL_STRINGSET_H
