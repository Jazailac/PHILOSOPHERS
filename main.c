#include "philo.h"

int main(int ac, char **av)
{
    t_simulation sim;
    pthread_t    monitor;
    int          i;

    if (parse_args(&sim, ac, av) != 0)
    {
        printf("Usage: %s nb_philo t_die t_eat t_sleep [must_eat]\n", av[0]);
        return (1);
    }
    if (init_simulation(&sim) != 0)
        return (1);
    sim.start_time = timestamp_ms();
    i = 0;
    if (sim.philo_count == 1)
    {
        print_action(&sim, sim.philos[i].id, "has taken a fork");
        smart_sleep(sim.time_to_die, &sim);
        print_action(&sim, sim.philos[i].id, "died");
        //lookout for leaks
        return (0);
    }
    while ( i < sim.philo_count)
    {
        philo_set_last_meal(&sim.philos[i], sim.start_time);
        pthread_create(&sim.philos[i].thread, NULL, philo_routine, &sim.philos[i]);
        i++;
    }
    pthread_create(&monitor, NULL, monitor_routine, &sim);
    for (i = 0; i < sim.philo_count; i++)
        pthread_join(sim.philos[i].thread, NULL);
    pthread_join(monitor, NULL);
    destroy_simulation(&sim);
    return (0);
}

