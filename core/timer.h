#ifndef TIMER_H_
#define TIMER_H_

#include "Api.h"
#include <chrono>

class COREAPI Timer
{
    public:
        Timer() { reset(); }
        std::chrono::microseconds ticks() const {
            using std::chrono::microseconds;
            using std::chrono::duration_cast;
            return duration_cast<microseconds>(clock::now() - m_timeStart);
        }
        void reset() {
            m_timeStart = clock::now();
        }
        static double ticksPerSecond() {
            double den = clock::duration::period::den;
            return den / clock::duration::period::num;
        }
    protected:
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable : 4251)
#endif
        using clock = std::chrono::steady_clock;
        clock::time_point m_timeStart;
#ifdef WIN32
#pragma warning(pop)
#endif
};

COREAPI uint64_t current_timestamp();
COREAPI uint64_t clear_global_timer();

#endif
