#include "philo.h"

int create_philos(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->philo_count)
    {
        if (pthread_create(&sim->philos[i].thread, NULL, philo_routine, &sim->philos[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

int one_philo(t_simulation *sim)
{
    print_action(sim, sim->philos[0].id, "has taken a fork");
    smart_sleep(sim->time_to_die, sim);
    print_action(sim, sim->philos[0].id, "died");
    destroy_simulation(sim);
    return (0);
}

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
    if (sim.philo_count == 1)
        return (one_philo(&sim));
    if (create_philos(&sim) != 0)
        return (1);
    pthread_create(&monitor, NULL, monitor_routine, &sim);
	i = 0;
    while (i < sim.philo_count)
        pthread_join(sim.philos[i++].thread, NULL);
    pthread_join(monitor, NULL);
    destroy_simulation(&sim);
    return (0);
}

