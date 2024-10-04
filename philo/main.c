/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:44:17 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/01 01:07:57 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_join_and_destroy(pthread_mutex_t *forks, t_args args, t_data *data)
{
	int	i;

	pthread_join(data->listener_thread, NULL);
	i = -1;
	while (++i < args.philos_nbr)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data->meals_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->time_mtx);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->args.time_to_eat);
	while (1)
	{
		ft_hold_forks(philo);
		ft_eat_state(philo);
		ft_release_forks(philo);
		ft_sleep_state(philo);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_args				args;
	t_data				data;
	t_philo				*philos;
	pthread_t			*threads;
	pthread_mutex_t		*forks;

	if (!ft_parse_param(argc, argv, &args))
	{
		ft_allocation(&philos, &forks, &threads, args);
		ft_init_data(forks, &data, args);
		ft_init_philos(philos, forks, &data, args);
		ft_create_threads(threads, philos, &data);
		ft_join_and_destroy(forks, args, &data);
	}
	else
		return (printf("Error Usage\n"), 1);
	return (0);
}
