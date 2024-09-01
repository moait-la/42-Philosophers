
#include "../Includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void ft_usleep(long milliseconds, t_philo *philos)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && philos->data->death_flag == 1)
		usleep(50);
}

int	ft_parse_param(int argc, char **argv, t_args *args)
{
	if (argc != 5 && argc != 6)
		return (1);
	args->philos_nbr = ft_atoi(argv[1]);
	if (args->philos_nbr <= 1)
		return (printf("invalid number of philosophers\n"), exit(1), -1);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat_nbr = ft_atoi(argv[5]);
	else
		args->must_eat_nbr = -1;
	return (0);
}

void	ft_init(t_philo *philos, pthread_mutex_t *forks, t_data *data, t_args args)
{
	int i;

	i = -1;
	while (++i < data->args->philos_nbr)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data->args->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_current_time();
        philos[i].left_fork = &forks[i];
        if (i == data->args->philos_nbr - 1)
            philos[i].right_fork = &forks[0];
        else
            philos[i].right_fork = &forks[i + 1];
        philos[i].data = data;
		philos[i].args = args;
	}
	data->start_time = get_current_time();
}
