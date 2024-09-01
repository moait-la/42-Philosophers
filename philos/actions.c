
#include "../Includes/philo.h"

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

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
