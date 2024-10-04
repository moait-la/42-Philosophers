/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:38:07 by moait-la          #+#    #+#             */
/*   Updated: 2024/10/01 08:16:48 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_print(t_philo *philo, char *action)
{
	long	passtime;

	pthread_mutex_lock(&philo->data->print_mtx);
	passtime = current_time() - philo->data->start_time;
	if (!ft_strcmp(action, "fork"))
		printf("%ld %d has taken a fork\n", passtime, philo->id);
	else if (!ft_strcmp(action, "eat"))
		printf("%ld %d is eating\n", passtime, philo->id);
	else if (!ft_strcmp(action, "sleep"))
		printf("%ld %d is sleeping\n", passtime, philo->id);
	else if (!ft_strcmp(action, "think"))
		printf("%ld %d is thinking\n", passtime, philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

void	ft_hold_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "fork");
	if (philo->args.philos_nbr == 1)
		return ;
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "fork");
}

void	ft_release_forks(t_philo *philo)
{
	if (philo->args.philos_nbr == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_eat_state(t_philo *philo)
{
	if (philo->args.philos_nbr == 1)
		return ;
	ft_print(philo, "eat");
	ft_usleep(philo->args.time_to_eat);
	pthread_mutex_lock(&philo->data->time_mtx);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->time_mtx);
	pthread_mutex_lock(&philo->data->meals_mtx);
	if (philo->args.must_eat_nbr != -1)
	{
		philo->eat_count += 1;
		if (philo->eat_count == philo->args.must_eat_nbr)
			philo->data->full_philos_count += 1;
	}
	pthread_mutex_unlock(&philo->data->meals_mtx);
}

void	ft_sleep_state(t_philo *philo)
{
	if (philo->args.philos_nbr == 1)
		return ;
	ft_print(philo, "sleep");
	ft_usleep(philo->args.time_to_sleep);
	ft_print(philo, "think");
}
