/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:33:00 by fio               #+#    #+#             */
/*   Updated: 2025/11/25 15:36:17 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}
void	philo_thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void print_status(t_philo *philo, char *str)
{
	long	timestamp;
	int		should_print;

	pthread_mutex_lock(&philo->data->stop_mutex);
	should_print = !philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (!should_print && ft_strcmp(str, "died") != 0)
		return ;
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);

	
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	long	current_time;
	
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while(i < data->nb_philos)
		{
			current_time = get_time();
			pthread_mutex_lock(&data->stop_mutex);
			if (current_time - data->philos[i].last_meal > data->time_to_die)
			{
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d died\n", current_time - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->stop_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

