#include <iostream>
#include <vector>
#include "RandomStringGenerator.h"
using namespace std;

void static printUsage(const char* name) {
    cerr << "Usage:\n"
         << name << " -g1 STRING_LEN NUM_STRINGS \tGenerate random data and send it to stdout\n"
         << "Generator parameters:\n"
         << "   STRING_LEN    Length of generated strings\n"
         << "   NUM_STRINGS   Number of generated strings\n"
         << endl;
}

static const char* const kName = "AALgenerator";
static const int kError = 1;

int g1Mode(vector<string> &args);
int main(int argc, char* argv[]) {
    vector<string> args(argv + 1, argv + argc + !argc);
    int ret;
    if (args.empty()) {
        printUsage(kName);
        return kError;
    }

    if (args[0] == "-g1") {
        ret = g1Mode(args);
    } else {
        ret = kError;
    }

    if (ret == kError) {
        printUsage(kName);
    }
    return ret;
}

int g1Mode(vector<string> &args) {
    if (args.size() != 3) {
        return kError;
    }

    ulong stringLength, numStrings;
    try {
        stringLength = stoul(args[1]);
        numStrings = stoul(args[2]);
    } catch (const logic_error &e) {
        cerr << e.what() << endl;
        return kError;
    }

    RandomStringGenerator rsg;
    StringSet set = rsg.generateStringSet(stringLength, numStrings);
    cout << set;
    return 0;
}

