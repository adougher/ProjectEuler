#include "timer.h"

static Timer s_timer_;

uint64_t
current_timestamp()
{
    return s_timer_.ticks().count();
}

uint64_t
clear_global_timer()
{
    s_timer_.reset();
    return s_timer_.ticks().count();
}

