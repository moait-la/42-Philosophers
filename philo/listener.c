/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:38:53 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/29 08:57:02 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_max_eat_check(t_philo *philo)
{
	if (philo[0].args.must_eat_nbr != -1)
	{
		pthread_mutex_lock(&philo[0].data->meals_mtx);
		if (philo[0].data->full_philos_count >= philo[0].args.philos_nbr)
			return (pthread_mutex_lock(&philo[0].data->print_mtx), 0);
		pthread_mutex_unlock(&philo[0].data->meals_mtx);
	}
	return (1);
}

void	*listener(void *arg)
{
	int		i;
	long	pass_time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philo[0].args.philos_nbr)
		{
			pthread_mutex_lock(&philo[0].data->time_mtx);
			pass_time = get_current_time() - philo[i].last_meal;
			if (pass_time > philo[i].args.time_to_die)
			{
				pthread_mutex_lock(&philo[0].data->print_mtx);
				pass_time = get_current_time() - philo[0].data->start_time;
				printf("%ld %d died\n", pass_time, philo[i].id);
				return (pthread_mutex_unlock(&philo[i].data->time_mtx), NULL);
			}
			pthread_mutex_unlock(&philo[i].data->time_mtx);
			if (!ft_max_eat_check(philo))
				return (NULL);
		}
	}
	return (NULL);
}

void	ft_create_threads(pthread_t *threads, t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	pthread_create(&data->listener_thread, NULL, &listener, philos);
	while (++i < data->args->philos_nbr)
	{
		pthread_create(&threads[i], NULL, &ft_routine, &philos[i]);
		pthread_detach(threads[i]);
	}
}
