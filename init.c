#include "philo.h"

int init_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            pthread_mutex_destroy(&data->data_lock);
            pthread_mutex_destroy(&data->print_lock);
            free(data->philos);
            free(data->forks);
            return (printf("Error : Fork Mutex init failed !\n"));
        }
        i++;
    }
    return (0);
}

int init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].data = data;
        i++;
    }
    return (0);
}

int init_data(t_data *data)
{
    data->eating_count = 0;
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    if (!data->philos)
        return (printf("Error : it's malloc's fault bro fr !\n"));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
    if (!data->forks)
    {
        free(data->philos);
        return (printf("Error : it's malloc fr\n"));
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
    {
        free(data->forks);
        free(data->philos);
        return (printf("Error : Mutex init failed !\n"));
    }
    if (pthread_mutex_init(&data->data_lock, NULL) != 0)
    {
        pthread_mutex_destroy(&data->print_lock);
        free(data->forks);
        free(data->philos);
        return (printf("Error : Mutex init failed !\n"));
    }
    if (pthread_mutex_init(&data->table_lock, NULL) != 0)
    {
        pthread_mutex_destroy(&data->print_lock);
        pthread_mutex_destroy(&data->data_lock);
        free(data->forks);
        free(data->philos);
        return (printf("Error : Mutex init failed !\n"));
    }
    if (init_philos(data) != 0 || init_forks(data) != 0)
        return (1);
    return (0);

}