#include "philo.h"

int is_digit(char *str)
{
    int i;

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

int check_input(t_data *data, char **av, int ac)
{
    if (ac < 5 || ac > 6)
        return (printf("Error : wrong number of arguments\n"));
    if (!is_digit(av[1]) ||!is_digit(av[2]) ||!is_digit(av[3]) ||!is_digit(av[4]))
        return (printf("Error : aruments must be positive integers !\n"));
    if (ac == 6)
    {
        if (!is_digit(av[5]))
            return (printf("Error : aruments must be positive integers !\n"));
        data->n_meals = ft_atoi(av[5]);
    }
    data->n_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (data->n_philos <= 0 || data->time_to_die < 0 || data->time_to_eat < 0 
    || data->time_to_sleep < 0 || data->n_philos > 200)
        return (printf("Error: Invalid argument value\n"), 1);
    if (data->n_meals <= 0 && ac == 6)
        return (printf("Error : number of meals must be greater than 0\n"));
    else if (ac != 6)
        data->n_meals = -1;
    return (0);
}

int check_data(t_data *data)
{
    if (data->n_philos <= 0 || data->n_philos > 200)
        return (0);
    if (data->time_to_die <= 0)
        return (0);
    if (data->time_to_eat <= 0)
        return (0);
    if (data->time_to_sleep <= 0)
        return (0);
    return (1);
}

int check_args(t_data *data, char **av, int ac)
{
    data->n_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->n_meals = -1;
    if (ac == 6)
    {
        data->n_meals = ft_atoi(av[5]);
        if (data->n_meals <= 0)
            return (0);
    }
    if (!check_data(data))
        return (0);
    return (1);
}