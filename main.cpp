#include <iostream>
#include <iomanip>
#include "data/RandomStringGenerator.h"
#include "algorithm/CommonStringFinder.h"
#include "algorithm/ExecutionTimeClock.h"

using namespace std;

void static printUsage(char* name) {
    cerr << "Usage:\n"
         << name << " -t1                            \tRead data from stdin and print results to stdout\n"
         << name << " -t2 <gen_options>              \tGenerate random data and print results to stdout\n"
         << name
         << " -t3 <gen_options> <test_params>\tGenerate random data, measure execution time and print results to stdout\n"
         << "Generator options:\n"
         << "\t-n STRING_LEN \tLength of generated strings\n"
         << "\t-m NUM_STRINGS\tNumber of generated strings\n"
         << "Test parameters:\n"
         << "\t-k NUM_GEN_SET     \tNumber of different generator settings\n"
         << "\t-step_n INC_STR_LEN\tIncrement of the length of generated strings\n"
         << "\t-step_m INC_NUM_STR\tIncrement of the number of generated strings\n"
         << "\t-r NUM_RUNS        \tNumber of algorithm runs per each generator setting\n"
         << endl;
}

void myPeekFunction(const char* key,
                    const StringSet &set,
                    const ulong* matchingLetters,
                    const std::list<ulong>* matchingStrings,
                    ulong currentStrIndex,
                    bool keyChanged) {
    char** data = set.getData();
    auto stringLength = set.getStringLength();
    cout << "Key: " << string(key, stringLength) << (keyChanged ? " (new)\n" : "\n");
    cout << setw(3) << left << currentStrIndex << ": " << string(data[currentStrIndex], stringLength) << endl;
    cout << "mL:  ";
    for (auto i = 0; i < currentStrIndex + 1; ++i) {
        cout << i << "(" << matchingLetters[i] << ")  ";
    }
    cout << "\nmS:\n";
    for (auto i = 0; i < stringLength; ++i) {
        cout << i << "(" << key[i] << "): [";
        for (auto it = matchingStrings[i].begin(); it != matchingStrings[i].end(); ++it) {
            if (it != matchingStrings[i].begin()) {
                cout << ", ";
            }
            cout << *it;
        }
        cout << "]\n";
    }
    cin.get();
}

int main(int argc, char* argv[]) {
//    printUsage("AAL");
//    for (string line; getline(cin, line);) {
//        cout << line << endl;
//    }

    RandomStringGenerator rsg;
    auto length = static_cast<ulong>(atol(argv[1]));
    auto numStrings = static_cast<ulong>(atoi(argv[2]));
    StringSet stringSet = rsg.generateStringSet(length, numStrings);
    for (ulong i = 0; i < numStrings; ++i) {
        for (ulong j = 0; j < length; ++j) {
            cout << stringSet.getData()[i][j];
        }
        cout << endl;
    }

    CommonStringFinder csf;
    cout << endl;
    cout << "Brute force: " << csf.bruteForce(stringSet) << endl << endl << endl;
//    cout << "Heuristic:   " << csf.heuristicInteractive(stringSet, myPeekFunction) << endl;

    ExecutionTimeClock<CommonStringFinder, CommonStringFinder::Result, StringSet> clock;
    auto result = clock.measure(&csf, &CommonStringFinder::bruteForce, stringSet);



    return 0;
}

