/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:33:00 by fio               #+#    #+#             */
/*   Updated: 2025/11/24 18:06:40 by anfiorit         ###   ########.fr       */
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

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_dead(t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	while(i < data->nb_philos)
	{
		current_time = get_time();
		if(current_time - data->philos[i].last_meal > data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			return(1);
		}
		i++;
	}
	return(0);
}

