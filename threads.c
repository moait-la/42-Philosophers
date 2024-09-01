#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PHILO_NBR 20
#define TIME_TO_DIE 400
#define TIME_TO_EAT 100
#define TIME_TO_SLEEP 100

typedef struct s_data
{
    int death_flag;
    long    start_time;
    pthread_mutex_t death_mutex; // Mutex for accessing death_flag
}   t_data;

typedef struct s_philo
{
    int     id;
    long    last_meal;
    t_data  *data;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
}   t_philo;

unsigned long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void ft_usleep(long milliseconds, t_philo *philos)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && philos->data->death_flag == 1)
		usleep(50);
}

void    init_philos(t_philo *philos, pthread_mutex_t *forks, t_data *data)
{
    int i;
    for (i = 0; i < PHILO_NBR; i++)
    {
        philos[i].id = i + 1;
        philos[i].last_meal = get_current_time();
        philos[i].left_fork = &forks[i];
        if (i == PHILO_NBR - 1)
            philos[i].right_fork = &forks[0];
        else
            philos[i].right_fork = &forks[i + 1];
        philos[i].data = data;
    }
}

void *is_dead(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philos[0].data->death_mutex);
        int i = 0;
        while (i < PHILO_NBR)
        {
            if (get_current_time() - philos[i].last_meal >= TIME_TO_DIE)
            {
                printf("%ld %d died\n", get_current_time() - philos[0].data->start_time, philos[i].id);
                philos[i].data->death_flag = 0;
                pthread_mutex_unlock(&philos[0].data->death_mutex);
                return NULL;
            }
            i++;
        }
        pthread_mutex_unlock(&philos[0].data->death_mutex);
    }
    return NULL;
}

void    *routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    philos->data->start_time = get_current_time();
    if (philos->id % 2 == 0)
        ft_usleep(TIME_TO_EAT, philos);
    while (1)
    {
        // pthread_mutex_lock(&philos->data->death_mutex);
        if (!philos->data->death_flag)
        {
            break ;
        }
        // pthread_mutex_unlock(&philos->data->death_mutex);

        pthread_mutex_lock(philos->left_fork);
        if (philos->data->death_flag == 1)
            printf("%ld %d has taken a fork\n", get_current_time() - philos->data->start_time, philos->id);

        pthread_mutex_lock(philos->right_fork);
        if (philos->data->death_flag == 1)
            printf("%ld %d has taken a fork\n", get_current_time() - philos->data->start_time, philos->id);

        if (philos->data->death_flag == 1)
            printf("%ld %d is eating\n", get_current_time() - philos->data->start_time, philos->id);
        ft_usleep(TIME_TO_EAT, philos); // milliseconds to microseconds

        pthread_mutex_lock(&philos->data->death_mutex);
        philos->last_meal = get_current_time();
        pthread_mutex_unlock(&philos->data->death_mutex);

        pthread_mutex_unlock(philos->left_fork);
        pthread_mutex_unlock(philos->right_fork);

        if (philos->data->death_flag == 1)
            printf("%ld %d is sleeping\n", get_current_time() - philos->data->start_time, philos->id);
        ft_usleep(TIME_TO_SLEEP, philos);
    }
    return (NULL);
}

int main()
{
    t_philo         *philos= malloc(sizeof(t_philo) * PHILO_NBR);
    pthread_t       threads[PHILO_NBR];
    pthread_t       scanner;
    pthread_mutex_t forks[PHILO_NBR];
    t_data          data;

    data.death_flag = 1;
    printf();
    pthread_mutex_init(&data.death_mutex, NULL);
    pthread_create(&scanner, NULL, &is_dead, philos);
    int i;
    for (i = 0; i < PHILO_NBR; i++)
        pthread_mutex_init(&forks[i], NULL);

    init_philos(philos, forks, &data);
 
    for (i = 0; i < PHILO_NBR; i++)
        pthread_create(&threads[i], NULL, &routine, &philos[i]);

    for (i = 0; i < PHILO_NBR; i++)
        pthread_join(threads[i], NULL);

    pthread_join(scanner, NULL);
    for (i = 0; i < PHILO_NBR; i++)
        pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(&data.death_mutex);
    return (0);
}





// void *is_dead(void *arg)
// {
//     t_philo *philos = (t_philo *)arg;
//     while (1)
//     {
//         for (int i = 0; i < PHILO_NBR; i++)
//         {
//             long current_time = get_current_time();
//             if (current_time - philos[i].last_meal >= TIME_TO_DIE)
//             {
//                 pthread_mutex_lock(&philos[i].data->death_mutex);
//                 if (philos[i].data->death_flag)
//                 {
//                     printf("%ld %d is dead\n", current_time - philos->start_time, philos[i].id);
//                     philos[i].data->death_flag = 0;
//                 }
//                 pthread_mutex_unlock(&philos[i].data->death_mutex);
//                 return NULL;
//             }
//         }
//         usleep(1000); // Sleep for 1 millisecond to avoid busy-waiting
//     }
//     return NULL;
// }




/*
    int fork_pairs[PHILO_NBR][2] = {
        {0, 1},  // Philosopher 0 uses forks 0 and 1
        {1, 2},  // Philosopher 1 uses forks 1 and 2
        {2, 3},  // Philosopher 2 uses forks 2 and 3
        {3, 4},  // Philosopher 3 uses forks 3 and 4
        {4, 0}   // Philosopher 4 uses forks 4 and 0 (wrap-around)
*/