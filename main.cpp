#include <iostream>
#include "generator/RandomStringGenerator.h"
#include "algorithm/CommonStringFinder.h"

using namespace std;

void static printUsage(char* name) {
    cerr << "Usage:\n"
         << name << " -t1                            \tRead data from stdin and print results to stdout\n"
         << name << " -t2 <gen_options>              \tGenerate random data and print results to stdout\n"
         << name << " -t3 <gen_options> <test_params>\tGenerate random data, measure execution time and print results to stdout\n"
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

int main(int argc, char* argv[]) {
//    printUsage("AAL");
//    for (string line; getline(cin, line);) {
//        cout << line << endl;
//    }

    RandomStringGenerator rsg;
    int length = 5;
    int numStrings = 10;
    StringSet stringSet = rsg.generateStringSet(length, numStrings);
    for (int i = 0; i < numStrings; ++i) {
        for (int j = 0; j < length; ++j) {
            cout << stringSet.getData()[i][j];
        }
        cout << endl;
    }

    CommonStringFinder csf;
    cout << endl;
    cout << "Brute force: " << csf.bruteForce(stringSet) << endl;
    cout << "Heuristic:   " << csf.heuristic(stringSet) << endl;

    return 0;
}

