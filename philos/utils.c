
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

void	ft_init_philos(t_philo *philos, pthread_mutex_t *forks, t_data *data, t_args args)
{
	int	i;

	i = -1;
	while (++i < data->args->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_current_time();
        philos[i].left_fork = &forks[i];
		if (data->args->philos_nbr > 1)
			philos[i].right_fork = &forks[(i + 1) % data->args->philos_nbr];
		philos[i].max_eat_reached = 1;
		philos[i].eat_count = 0;
        philos[i].data = data;
		philos[i].args = args;
	}
}

void	ft_init_data(pthread_mutex_t *forks, t_data *data, t_args args)
{
	int i;

	i = -1;
	while (++i < data->args->philos_nbr)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->start_time = get_current_time();
	data->death_flag = 1;
	data->been_here = 1;
	data->stop_flag = 1;
	data->args = &args;
}
