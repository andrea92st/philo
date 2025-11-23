#ifndef PHILO_H
# define PHILO_H

		// LIBRARY //
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

		// STRUCT //
typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef struct s_data
{
    int     nb_philos;
    long    time_to_eat;
    long    time_to_die;
    long    time_to_sleep;
    int     must_eat;
    t_philo   *philos;
}  t_data;

typedef struct s_philo
{
    int    id;
    t_data  *data;
	pthread_t thread;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
}   t_philo;


		// FONCTIONS //
int		main(int ac, char **av);

		// PARSING //
int		*convert_into_int(int ac, char **av);
int		ft_atoi(const char *str);

		// INIT //
void	init_philo(t_data *data);
void 	init_data(t_data *data, int *tab, int ac);
void	init_thread(t_data *data);

		// ACTIONS //
void	*routine(void *arg);

#endif