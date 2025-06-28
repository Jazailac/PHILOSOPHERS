#include "philo.h"

int init_data(t_data *data);

void ll(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_data	data;

	// atexit(ll);
	if (check_input(&data, argv, argc) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	if (start_simulation(&data) != 0)
		return (cleanup(&data), 1);
	cleanup(&data);
	return (0);
}