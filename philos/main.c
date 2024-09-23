#include "../Includes/philo.h"

void	ft_join_and_destroy(pthread_t *threads, pthread_mutex_t *forks, t_args args, t_data *data)
{
	int i;

	i = -1;
	while (++i < args.philos_nbr)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_join(data->listener_thread, NULL);
	i = -1;
	while(++i < args.philos_nbr)
		pthread_mutex_destroy(&forks[i]);
	
}

void	*ft_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(philo->args.time_to_eat, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (!philo->data->death_flag)
			return (pthread_mutex_unlock(&philo->data->death_mutex), NULL);
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_hold_forks(philo);
		ft_eat_state(philo);
		ft_release_forks(philo);
		ft_sleep_state(philo);
		if (philo->eat_count == philo->args.must_eat_nbr)
		{
			philo->data->stop_flag = 0;
			break ;
		}
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_args				args;
	t_data				data;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_t			*threads;

	if (!ft_parse_param(argc, argv, &args))
	{
		ft_allocation(&philos, &forks, &threads, args);
		ft_init_data(forks, &data, args);
		ft_init_philos(philos, forks, &data, args);
		ft_create_threads(threads, philos, &data);
		ft_join_and_destroy(threads, forks, args, &data);
	}
	else
		return (printf("Error Usage\n"), 1);
	return 0;
}
