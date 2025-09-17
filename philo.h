#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_simulation t_simulation;
typedef struct s_philo t_philo;

struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal;      /* timestamp in ms */
    pthread_t       thread;
    pthread_mutex_t meal_lock;      /* protects meals_eaten & last_meal */
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_simulation    *sim;
};

struct s_simulation
{
    int             philo_count;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    long long       start_time;
    int             stop;

    int             finished_count;       /* NEW: philosophers who finished */
    pthread_mutex_t finish_lock;          /* protects finished_count */

    pthread_mutex_t stop_lock;
    pthread_mutex_t print_lock;
    pthread_mutex_t *forks;
    t_philo         *philos;
};

/* time utils */
long long   timestamp_ms(void);
void        smart_sleep(long long ms, t_simulation *sim);

/* philosopher getters/setters (thread-safe) */
int         philo_get_meals(t_philo *p);
void        philo_inc_meals(t_philo *p);
void        philo_set_meals(t_philo *p, int v);
long long   philo_get_last_meal(t_philo *p);
void        philo_set_last_meal(t_philo *p, long long tm);
void sim_inc_finished(t_simulation *sim);
int sim_get_finished(t_simulation *sim);

/* simulation getters/setters (thread-safe) */
int         sim_get_stop(t_simulation *sim);
void        sim_set_stop(t_simulation *sim, int value);

/* printing */
void        print_action(t_simulation *sim, int id, const char *action);

/* initialization / cleanup */
int         parse_args(t_simulation *sim, int ac, char **av);
int         init_simulation(t_simulation *sim);
void        destroy_simulation(t_simulation *sim);

/* routine + monitor */
void        *philo_routine(void *arg);
void        *monitor_routine(void *arg);


/*parsing*/
int is_digit(char *str);
#endif

