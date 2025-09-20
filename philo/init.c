/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:09:12 by jazailac          #+#    #+#             */
/*   Updated: 2025/09/19 21:11:15 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static	int	ft_atoi(const char *s)
{
	long long	n;

	n = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		n *= 10;
		n += *s - '0';
		s++;
	}
	if (*s == '\0')
		return ((int)n);
	return (-1);
}

int	parse_args(t_simulation *sim, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (!is_digit(av[1]) ||!is_digit(av[2])
		||!is_digit(av[3]) || !is_digit(av[4]) 
		|| (ac == 6 && !is_digit(av[5])))
		return (printf("Error : aruments must be positive integers !\n"));
	sim->philo_count = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		sim->must_eat = ft_atoi(av[5]);
	else
		sim->must_eat = -1;
	if ((sim->philo_count < 1 || sim->philo_count > 200) 
		|| sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
		return (1);
	return (0);
}

void	init_locks(t_simulation *sim)
{
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->stop_lock, NULL);
	pthread_mutex_init(&sim->finish_lock, NULL);
}

int	init_simulation(t_simulation *sim)
{
	int	i;

	sim->stop = 0;
	sim->finished_count = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (!sim->forks || !sim->philos)
		return (1);
	init_locks(sim);
	i = 0;
	while (i < sim->philo_count)
		pthread_mutex_init(&sim->forks[i++], NULL);
	i = 0;
	while (i < sim->philo_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = 0;
		pthread_mutex_init(&sim->philos[i].meal_lock, NULL);
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->philo_count];
		sim->philos[i].sim = sim;
		i++;
	}
	return (0);
}
