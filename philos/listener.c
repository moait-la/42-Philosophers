
#include "../Includes/philo.h"

void	*listener_thread(void *arg)
{
	int	i;
	long	pass_time;

	t_philo	*philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos[0].data->death_mutex);
		i = -1;
		while (++i < philos[0].args.philos_nbr)
		{
			if (get_current_time() - philos[i].last_meal > philos[i].args.time_to_die)
			{
				philos[i].data->death_flag = 0;
				pass_time = get_current_time() - philos[0].data->start_time;
				printf("%ld %d died\n", pass_time, philos[i].id);
				pthread_mutex_unlock(&philos[0].data->death_mutex);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philos[0].data->death_mutex);
	}
	return (NULL);
}

void	ft_create_threads(pthread_t *threads, t_philo *philos, t_data *data)
{
	pthread_create(&data->listener_thread, NULL, &listener_thread, philos);
	int i = -1;
	while (++i < data->args->philos_nbr)
		pthread_create(&threads[i], NULL, &ft_routine, &philos[i]);
}
