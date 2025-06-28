#include "philo.h"

void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
void    print_status(t_philo *philo, char *status);

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->n_philos == 1)
	{
		print_status(philo, "has taken a fork");
		precise_usleep(data->time_to_die, data);
		// print_status(philo, "died");
		// pthread_mutex_lock(&data->data_lock);
		// data->end_sim = 1;
		// pthread_mutex_unlock(&data->data_lock);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(data->time_to_eat, data);
	while (1)
	{
		pthread_mutex_lock(&data->data_lock);
		if (data->end_sim)
		{
			pthread_mutex_unlock(&data->data_lock);
			break;
		}
		pthread_mutex_unlock(&data->data_lock);
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}