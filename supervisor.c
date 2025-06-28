#include "philo.h"

void *philosopher_routine(void *arg);
void print_status(t_philo *philo, char *status);

static int check_death(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_lock(&data->data_lock);
        if (get_current_time() - data->philos[i].last_meal_time > data->time_to_die)
        {
            pthread_mutex_unlock(&data->data_lock);
            print_status(&data->philos[i], "died");
            pthread_mutex_lock(&data->data_lock);
            data->end_sim = 1;
            pthread_mutex_unlock(&data->data_lock);
            return (1);
        }
        pthread_mutex_unlock(&data->data_lock);
        i++;
    }
    return (0);
}

static int check_meal(t_data *data)
{
    int i;
    int finished;

    i = 0;
    finished = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_lock(&data->data_lock);
        if (data->philos[i].meals_eaten >= data->n_meals)
            finished++;
        pthread_mutex_unlock(&data->data_lock);
        i++;
    }
    if (finished == data->n_philos)
    {
        pthread_mutex_lock(&data->data_lock);
        data->end_sim = 1;
        pthread_mutex_unlock(&data->data_lock);
        return (1);
    }
    return(0);
}

int start_simulation(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_current_time();
    data->end_sim = 0;
    while (i <data->n_philos)
    {
        data->philos[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philos[i].thread, NULL, &philosopher_routine, &data->philos[i]) != 0)
            return (printf("Failed to create a thread\n"));
        
        i++;
    }
    while (1)
    {
        if (check_death(data))
            break;
        if (data->n_meals > 0 && check_meal(data)) 
            break;
        usleep(100);
    }
    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            return (printf("Failed to join threads\n"));
        i++;
    }
    return (0);
}