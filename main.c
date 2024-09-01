#include "./Includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

int	ft_parse_param(int argc, char **argv, t_args *args)
{
	if (argc != 5 && argc != 6)
		return (1);
	args->philos_nbr = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat_nbr = ft_atoi(argv[5]);
	else
		args->must_eat_nbr = -1;
	return (0);
}

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


//*****
void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_hold_forks(t_philo *philos)
{
	long	pass_time;

	pthread_mutex_lock(philos->left_fork);
	if (philos->data->death_flag != 0)
	{
		pass_time = get_current_time() - philos->data->start_time;
		printf("%ld %d has taken a left fork\n", pass_time, philos->id);
	}
	pthread_mutex_lock(philos->right_fork);
	if (philos->data->death_flag != 0)
	{
		pass_time = get_current_time() - philos->data->start_time;
		printf("%ld %d has taken a right fork\n", pass_time, philos->id);
	}
}
// ----
void ft_usleep(long milliseconds, t_philo *philos)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && philos->data->death_flag == 1)
		usleep(50);
}

void	ft_eat_state(t_philo *philo)
{
	long	pass_time;
	if (philo->data->death_flag != 0)
	{
		pass_time = get_current_time() - philo->data->start_time;
		printf("%ld %d is eating\n", pass_time, philo->id);
		ft_usleep(philo->args.time_to_eat, philo);
	}
}


void	ft_sleep_state(t_philo *philo)
{
	long	pass_time;

	if (philo->data->death_flag != 0)
	{
		pass_time = get_current_time() - philo->data->start_time;
		printf("%ld %d is sleeping\n", pass_time, philo->id);
		ft_usleep(philo->args.time_to_sleep, philo);
	}
}
// ---
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

void	ft_create_threads(pthread_t *threads, t_philo *philos, t_data *data)
{
	pthread_create(&data->listener_thread, NULL, &listener_thread, philos);
	int i = -1;
	while (++i < data->args->philos_nbr)
		pthread_create(&threads[i], NULL, &ft_routine, &philos[i]);
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

		int i = 0;
		while (i < args.philos_nbr)
		{
			pthread_join(threads[i], NULL);
			i++;
		}

	}
	else
		return (printf("Error: Usage!\n"), 1);
	return 0;
}
