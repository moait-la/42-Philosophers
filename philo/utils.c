/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:50:17 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/30 06:18:47 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
		usleep(200);
}

void	ft_init_philos(t_philo *philos, pthread_mutex_t *forks, \
			t_data *data, t_args args)
{
	int	i;

	i = -1;
	while (++i < data->args->philos_nbr)
	{
		philos[i].last_meal = current_time();
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[i];
		if (data->args->philos_nbr > 1)
			philos[i].right_fork = &forks[((i + 1) % data->args->philos_nbr)];
		philos[i].eat_count = 0;
		philos[i].data = data;
		philos[i].args = args;
	}
}

void	ft_init_data(pthread_mutex_t *forks, t_data *data, t_args args)
{
	int	i;

	i = -1;
	while (++i < args.philos_nbr)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&data->meals_mtx, NULL);
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->time_mtx, NULL);
	data->start_time = current_time();
	data->args = &args;
	data->full_philos_count = 0;
}
