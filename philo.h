#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


struct s_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				n_meals; 

	long long		start_time;
	int				end_sim;

	t_philo			*philos;
	pthread_mutex_t	*forks;

	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
	pthread_mutex_t    table_lock;  
    int                eating_count; 
}	t_data;


int     check_input(t_data *data, char **av, int ac);
void	cleanup(t_data *data);

long long	get_current_time(void);
long		ft_atoi(const char *str);
void		precise_usleep(long long duration_ms, t_data *data);


int	init_philos(t_data *data);
int	init_forks(t_data *data);
int init_data(t_data *data);


int	start_simulation(t_data *data);
void	*philosopher_routine(void *arg);

void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
#endif