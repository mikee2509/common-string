#include "ExecutionTimeClock.h"
using namespace std;
using namespace std::chrono;

long long ExecutionTimeClock::measure(function<void()> function) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    function();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}
