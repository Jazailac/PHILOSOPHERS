#include "philo.h"

void *monitor_routine(void *arg)
{
    t_simulation *sim;
    int i;

    sim = (t_simulation *)arg;
    while (!sim_get_stop(sim))
    {
        // Check if all philosophers have finished eating required meals
        if (sim->must_eat != -1 && sim_get_finished(sim) >= sim->philo_count)
        {
            sim_set_stop(sim, 1);
            return (NULL);
        }
        
        i = 0;
        while (i < sim->philo_count)
        {
            long long since;

            since = timestamp_ms() - philo_get_last_meal(&sim->philos[i]);
            if (sim->philos[i].last_meal != 0 && since > sim->time_to_die)
            {
                print_action(sim, sim->philos[i].id, "died");
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}