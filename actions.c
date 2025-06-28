#include "philo.h"

void    print_status(t_philo *philo, char *status)
{
	long long	time_ms;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->data_lock);
	if (philo->data->end_sim)
	{
		pthread_mutex_unlock(&philo->data->data_lock);
		pthread_mutex_unlock(&philo->data->print_lock);
		return;
	}
	pthread_mutex_unlock(&philo->data->data_lock);
	time_ms = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", time_ms, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->data->forks[philo->id - 1];
	right_fork = &philo->data->forks[philo->id % philo->data->n_philos];
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(left_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_lock);
	philo->meals_eaten++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->data_lock);
	precise_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}


void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	long long think_time;
	
	print_status(philo, "is thinking");
	if (philo->data->n_philos % 2 == 1)
	{
		think_time = (philo->data->time_to_eat - philo->data->time_to_sleep);
		if (think_time <= 0)
			think_time = 1;
		if (think_time > philo->data->time_to_eat)
			think_time = philo->data->time_to_eat / 2;
		precise_usleep(think_time, philo->data);
	}
}
