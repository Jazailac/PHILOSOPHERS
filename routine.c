/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazailac <jazailac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:22:08 by jazailac          #+#    #+#             */
/*   Updated: 2025/09/19 21:23:08 by jazailac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_action(p->sim, p->id, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_action(p->sim, p->id, "has taken a fork");
	print_action(p->sim, p->id, "is eating");
	philo_set_last_meal(p, timestamp_ms());
	smart_sleep(p->sim->time_to_eat, p->sim);
	philo_inc_meals(p);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!sim_get_stop(p->sim))
	{
		eat(p);
		if (p->sim->must_eat != -1 && philo_get_meals(p) >= p->sim->must_eat)
		{
			sim_inc_finished(p->sim);
			break ;
		}
		print_action(p->sim, p->id, "is sleeping");
		smart_sleep(p->sim->time_to_sleep, p->sim);
		print_action(p->sim, p->id, "is thinking");
	}
	return (NULL);
}
