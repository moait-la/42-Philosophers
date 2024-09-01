#ifndef PHILO_H
#define PHILO_H

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
	int				death_flag;
	long			start_time;
	pthread_t		listener_thread;
	pthread_mutex_t	death_mutex;
	t_args			*args;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
	t_data			*data;
	t_args			args;
}	t_philo;

int	ft_atoi(const char *str);

#endif
