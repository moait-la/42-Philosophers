/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:37:46 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/23 20:52:40 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

int	ft_parse_param(int argc, char **argv, t_args *args)
{
	if (argc != 5 && argc != 6)
		return (1);
	args->philos_nbr = ft_atoi(argv[1]);
	if (args->philos_nbr <= 0)
		return (printf("invalid number of philosophers\n"), exit(1), -1);
	if ((args->time_to_die = ft_atoi(argv[2])) < 0)
		return (printf("invalid time_to_die\n"), exit(1), -1);
	if ((args->time_to_eat = ft_atoi(argv[3])) < 0)
		return (printf("invalid time_to_eat\n"), exit(1), -1);
	if ((args->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (printf("invalid time_to_sleep\n"), exit(1), -1);
	if (argc == 6)
		args->must_eat_nbr = ft_atoi(argv[5]);
	if (args->must_eat_nbr <= 0)
		return (printf("invalid number_of_times_each_philosopher_must_eat\n"), exit(1), -1);
	return (0);
}

void	ft_allocation(t_philo **philos, pthread_mutex_t **forks, pthread_t **threads, t_args args)
{
	(*philos) = (t_philo *)malloc(sizeof(t_philo) * args.philos_nbr);
	if (!*philos)
		return (printf("Error: allocating\n"), exit(1));
	(*threads) = (pthread_t *)malloc(sizeof(pthread_t) * args.philos_nbr);
	if (!*threads)
		return (printf("Error: allocating\n"), exit(1));
	(*forks) = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args.philos_nbr);
	if (!*forks)
		return (printf("Error: allocating\n"), exit(1));
}
