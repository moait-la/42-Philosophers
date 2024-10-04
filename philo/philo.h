/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 08:34:59 by moait-la          #+#    #+#             */
/*   Updated: 2024/09/30 06:45:45 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_args
{
	int	philos_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_nbr;
}	t_args;

typedef struct s_data
{
	int				full_philos_count;
	long			start_time;
	pthread_t		listener_thread;
	pthread_mutex_t	time_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	meals_mtx;
	t_args			*args;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
	t_args			args;
}	t_philo;

void	*ft_routine(void *arg);

void	ft_hold_forks(t_philo *philos);
void	ft_release_forks(t_philo *philo);
void	ft_eat_state(t_philo *philo);
void	ft_sleep_state(t_philo *philo);
int		ft_parse_param(int argc, char **argv, t_args *args);
long	current_time(void);
int		ft_strcmp(char *s1, char *s2);
void	ft_init_data(pthread_mutex_t *forks, t_data *data, t_args args);
void	ft_init_philos(t_philo *philos, pthread_mutex_t *forks, \
			t_data *data, t_args args);
void	ft_usleep(long milliseconds);
void	ft_allocation(t_philo **philos, pthread_mutex_t **forks, \
			pthread_t **threads, t_args args);
void	*listener(void *arg);
void	ft_create_threads(pthread_t *threads, t_philo *philos, t_data *data);
int		ft_atoi(const char *str);

#endif
