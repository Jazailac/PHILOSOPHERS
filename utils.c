#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long long duration_ms, t_data *data)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < duration_ms)
	{
		pthread_mutex_lock(&data->data_lock);
		if (data->end_sim)
		{
			pthread_mutex_unlock(&data->data_lock);
			break;
		}
		pthread_mutex_unlock(&data->data_lock);
		usleep(500);
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->table_lock);
}