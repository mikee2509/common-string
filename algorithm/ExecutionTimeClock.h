#ifndef AAL_EXECUTIONTIMECLOCK_H
#define AAL_EXECUTIONTIMECLOCK_H

#include <chrono>
#include <functional>

class ExecutionTimeClock {
public:
    long long measure(std::function<void()> function);
};

#endif //AAL_EXECUTIONTIMECLOCK_H
