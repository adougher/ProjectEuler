#include "timer.h"

static vmt::util::Timer s_timer_;

uint64_t
vmt::util::current_timestamp()
{
    return s_timer_.ticks().count();
}

uint64_t
vmt::util::clear_global_timer()
{
    s_timer_.reset();
    return s_timer_.ticks().count();
}

