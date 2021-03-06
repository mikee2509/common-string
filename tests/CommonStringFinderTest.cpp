#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include "../data/RandomStringGenerator.h"
#include "../algorithm/CommonStringFinder.h"

using namespace std;
using ::testing::Combine;
using ::testing::Range;

class CommonStringFinderTest : public ::testing::TestWithParam<::testing::tuple<ulong, ulong>> {
protected:
    RandomStringGenerator rsg;
    StringSet* set = nullptr;
    CommonStringFinder csf;
    void SetUp() override {
        ulong stringLength = ::testing::get<0>(GetParam());
        ulong numStrings = ::testing::get<1>(GetParam());
        set = new StringSet(stringLength, numStrings);
        rsg.fillStringSet(*set);
    }

    void TearDown() override {
        delete set;
        set = nullptr;
    }
};


static ulong numSuccesses = 0;

// Check if solutions found by heuristic are correct
class HeuristicCorrectnessTest : public CommonStringFinderTest {
public:
    static void TearDownTestCase() {
        cout << "Number of solutions checked for correctness: " << numSuccesses << endl;
    }
};

TEST_P(HeuristicCorrectnessTest, T1) {
    auto result = csf.heuristic(*set);
    if (result.solutionFound()) {
        EXPECT_TRUE(csf.doesKeyMatch(result.value, *set));
        ++numSuccesses;
        return;
    }
}

INSTANTIATE_TEST_CASE_P(CSFTests, HeuristicCorrectnessTest,
                        Combine(Range(ulong(10), ulong(100), ulong(1)),
                                Range(ulong(10), ulong(1000), ulong(10))));

// Check heuristic success rate
class HeuristicSuccessRateTest : public CommonStringFinderTest {
protected:
    const ulong numAttempts = 1000;
    const int minSuccessRate = 90;
    const int w = 4;
};

static vector<double> rates(15, -1.0);

TEST_P(HeuristicSuccessRateTest, T2) {
    ulong strLen = set->getStringLength();
    if (rates[strLen] != -1.0 && (isnan(rates[strLen]) || rates[strLen] < minSuccessRate)) {
        return;
    }
    ulong bruSuccesses = 0;
    ulong heuSuccesses = 0;
    for (ulong i = 0; i < numAttempts; ++i) {
        auto bruResult = csf.bruteForce(*set);
        if (bruResult.solutionFound()) {
            ++bruSuccesses;
            auto heuResult = csf.heuristic(*set);
            if (heuResult.solutionFound()) {
                ++heuSuccesses;
            }
        }
        rsg.fillStringSet(*set);
    }
    double sr = (double) heuSuccesses * 100 / bruSuccesses;
    rates[strLen] = sr;
    cout << endl
         << "strLen: " << strLen
         << "\tnumStr: " << set->getNumStrings()
         << "\t" << setw(w) << right << heuSuccesses << "/" << setw(w) << left << bruSuccesses
         << "\tSR = " << fixed << right << setw(5) << setprecision(1) << sr << " %"
         << endl;
}

INSTANTIATE_TEST_CASE_P(CSFTests, HeuristicSuccessRateTest,
                        Combine(Range(ulong(1), ulong(15), ulong(1)),
                                Range(ulong(1), ulong(1000), ulong(5))));


