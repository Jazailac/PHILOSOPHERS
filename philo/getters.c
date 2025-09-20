/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:05:53 by jazailac          #+#    #+#             */
/*   Updated: 2025/09/19 21:06:48 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_get_finished(t_simulation *sim)
{
	int	v;

	pthread_mutex_lock(&sim->finish_lock);
	v = sim->finished_count;
	pthread_mutex_unlock(&sim->finish_lock);
	return (v);
}

void	sim_inc_finished(t_simulation *sim)
{
	pthread_mutex_lock(&sim->finish_lock);
	sim->finished_count++;
	pthread_mutex_unlock(&sim->finish_lock);
}

int	philo_get_meals(t_philo *p)
{
	int	v;

	pthread_mutex_lock(&p->meal_lock);
	v = p->meals_eaten;
	pthread_mutex_unlock(&p->meal_lock);
	return (v);
}

void	philo_inc_meals(t_philo *p)
{
	pthread_mutex_lock(&p->meal_lock);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_lock);
}

long long	philo_get_last_meal(t_philo *p)
{
	long long	v;

	pthread_mutex_lock(&p->meal_lock);
	v = p->last_meal;
	pthread_mutex_unlock(&p->meal_lock);
	return (v);
}
