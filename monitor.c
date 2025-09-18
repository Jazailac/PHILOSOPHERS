#include "philo.h"

int check_death(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->philo_count)
    {
        long long since;

        since = timestamp_ms() - philo_get_last_meal(&sim->philos[i]);
        if (philo_get_last_meal(&sim->philos[i]) != 0 && since > sim->time_to_die)
        {
            print_action(sim, sim->philos[i].id, "died");
            return (0);
        }
        i++;
    }
    return (1);
}

void *monitor_routine(void *arg)
{
    t_simulation *sim;

    sim = (t_simulation *)arg;
    while (!sim_get_stop(sim))
    {
        if (sim->must_eat != -1 && sim_get_finished(sim) >= sim->philo_count)
        {
            sim_set_stop(sim, 1);
            return (NULL);
        }
        if (!check_death(sim))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}