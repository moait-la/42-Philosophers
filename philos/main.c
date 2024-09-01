#include "../Includes/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	philo->data->start_time = get_current_time();
	if (philo->id % 2 == 0)
		ft_usleep(philo->args.time_to_eat, philo);
	while (1)
	{
		if (!philo->data->death_flag)
			break ;
		ft_hold_forks(philo);
		ft_eat_state(philo);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_release_forks(philo);
		ft_sleep_state(philo);
	}
	return (NULL);
}

void	ft_join_and_destroy(pthread_t *threads, pthread_mutex_t *forks, t_args args)
{
	int i;

	i = -1;
	while (++i < args.philos_nbr)
		pthread_join(threads[i], NULL);
	i = -1;
	while(++i < args.philos_nbr)
		pthread_mutex_destroy(&forks[i]);
}

int main(int argc, char *argv[])
{
	t_args				args;
	t_data				data;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_t			*threads;

	data.death_flag = 1;
	data.args = &args;
	pthread_mutex_init(&data.death_mutex, NULL);
	if (!ft_parse_param(argc, argv, &args))
	{
		philos = (t_philo *)malloc(sizeof(t_philo) * args.philos_nbr);
		forks = malloc(sizeof(pthread_mutex_t) * args.philos_nbr);
		threads = malloc(sizeof(pthread_t) * args.philos_nbr);
		ft_init(philos, forks, &data, args);
		ft_create_threads(threads, philos, &data);
		ft_join_and_destroy(threads, forks, args);
	}
	else
		return (printf("Error Usage\n"), 1);
	return 0;
}
