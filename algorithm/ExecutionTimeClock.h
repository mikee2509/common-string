//
// Created by michal on 04.01.18.
//

#ifndef AAL_EXECUTIONTIMECLOCK_H
#define AAL_EXECUTIONTIMECLOCK_H

#include <chrono>

template<typename Class, typename Ret, typename Arg>
class ExecutionTimeClock {
public:
    struct MeasureResult {
        long time;
        Ret returnValue;

        MeasureResult(long time, Ret returnValue) : time(time), returnValue(returnValue) {}
    };

    typename ExecutionTimeClock<Class, Ret, Arg>::MeasureResult measure(Class* cl, Ret (Class::*fptr)(Arg &), Arg &arg);
};

template<typename Class, typename Ret, typename Arg>
typename ExecutionTimeClock<Class, Ret, Arg>::MeasureResult
ExecutionTimeClock<Class, Ret, Arg>::measure(Class* cl, Ret (Class::*fptr)(Arg &), Arg &arg) {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Ret returnValue = (cl->*fptr)(arg);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    long measuredTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    return MeasureResult(measuredTime, returnValue);
}

#endif //AAL_EXECUTIONTIMECLOCK_H
