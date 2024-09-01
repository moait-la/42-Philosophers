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

void	*ft_routine(void *arg);

void	ft_hold_forks(t_philo *philos);
void	ft_release_forks(t_philo *philo);
void	ft_eat_state(t_philo *philo);
void	ft_sleep_state(t_philo *philo);

int		ft_parse_param(int argc, char **argv, t_args *args);
long	get_current_time(void);
void	ft_init(t_philo *philos, pthread_mutex_t *forks, t_data *data, t_args args);
void	 ft_usleep(long milliseconds, t_philo *philos);

void	*listener_thread(void *arg);
void	ft_create_threads(pthread_t *threads, t_philo *philos, t_data *data);

int		ft_atoi(const char *str);

#endif
