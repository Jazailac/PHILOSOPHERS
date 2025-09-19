/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:24:16 by jazailac          #+#    #+#             */
/*   Updated: 2025/09/19 21:24:41 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_meals(t_philo *p, int v)
{
	pthread_mutex_lock(&p->meal_lock);
	p->meals_eaten = v;
	pthread_mutex_unlock(&p->meal_lock);
}

void	philo_set_last_meal(t_philo *p, long long tm)
{
	pthread_mutex_lock(&p->meal_lock);
	p->last_meal = tm;
	pthread_mutex_unlock(&p->meal_lock);
}

void	sim_set_stop(t_simulation *sim, int value)
{
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = value;
	pthread_mutex_unlock(&sim->stop_lock);
}

int	sim_get_stop(t_simulation *sim)
{
	int	v;

	pthread_mutex_lock(&sim->stop_lock);
	v = sim->stop;
	pthread_mutex_unlock(&sim->stop_lock);
	return (v);
}

void	print_action(t_simulation *sim, int id, const char *action)
{
	long long	ts;

	pthread_mutex_lock(&sim->print_lock);
	ts = timestamp_ms() - sim->start_time;
	if (!sim_get_stop(sim))
	{
		if (ft_strcmp(action, "died") == 0)
		{
			sim_set_stop(sim, 1);
			printf("%lld %d %s\n", ts, id, action);
		}
		else
			printf("%lld %d %s\n", ts, id, action);
	}
	pthread_mutex_unlock(&sim->print_lock);
}
