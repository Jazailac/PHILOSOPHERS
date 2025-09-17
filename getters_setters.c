#include "philo.h"

/* ---- Philosopher-safe accessors ---- */

int sim_get_finished(t_simulation *sim)
{
    int v;
    pthread_mutex_lock(&sim->finish_lock);
    v = sim->finished_count;
    pthread_mutex_unlock(&sim->finish_lock);
    return (v);
}

void sim_inc_finished(t_simulation *sim)
{
    pthread_mutex_lock(&sim->finish_lock);
    sim->finished_count++;
    pthread_mutex_unlock(&sim->finish_lock);
}

int philo_get_meals(t_philo *p)
{
    int v;
    pthread_mutex_lock(&p->meal_lock);
    v = p->meals_eaten;
    pthread_mutex_unlock(&p->meal_lock);
    return (v);
}

void  philo_inc_meals(t_philo *p)
{
    pthread_mutex_lock(&p->meal_lock);
    p->meals_eaten++;
    pthread_mutex_unlock(&p->meal_lock);
}

void philo_set_meals(t_philo *p, int v)
{
    pthread_mutex_lock(&p->meal_lock);
    p->meals_eaten = v;
    pthread_mutex_unlock(&p->meal_lock);
}

long long philo_get_last_meal(t_philo *p)
{
    long long v;
    pthread_mutex_lock(&p->meal_lock);
    v = p->last_meal;
    pthread_mutex_unlock(&p->meal_lock);
    return (v);
}

void philo_set_last_meal(t_philo *p, long long tm)
{
    pthread_mutex_lock(&p->meal_lock);
    p->last_meal = tm;
    pthread_mutex_unlock(&p->meal_lock);
}


int sim_get_stop(t_simulation *sim)
{
    int v;
    pthread_mutex_lock(&sim->stop_lock);
    v = sim->stop;
    pthread_mutex_unlock(&sim->stop_lock);
    return (v);
}

void sim_set_stop(t_simulation *sim, int value)
{
    pthread_mutex_lock(&sim->stop_lock);
    sim->stop = value;
    pthread_mutex_unlock(&sim->stop_lock);
}

/* ---- Printing helper ---- */
void print_action(t_simulation *sim, int id, const char *action)
{
    long long ts;

    pthread_mutex_lock(&sim->print_lock);
    ts = timestamp_ms() - sim->start_time;
    if (!sim_get_stop(sim))
    {
        if (strcmp(action, "died") == 0)
        {
            sim_set_stop(sim, 1);
            printf("%lld %d %s\n", ts, id, action);
        }
        else
            printf("%lld %d %s\n", ts, id, action);
    }
    pthread_mutex_unlock(&sim->print_lock);
}

