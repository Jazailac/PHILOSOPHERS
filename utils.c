#include "philo.h"

/* Return current timestamp in milliseconds */
long long timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/* Sleep roughly `ms` milliseconds but wake early if simulation stops */
void smart_sleep(long long ms, t_simulation *sim)
{
    long long start = timestamp_ms();
    while (!sim_get_stop(sim))
    {
        if (timestamp_ms() - start >= ms)
            break;
        usleep(500); /* 0.5ms increments */
    }
}
