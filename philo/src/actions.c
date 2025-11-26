/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:33:00 by fio               #+#    #+#             */
/*   Updated: 2025/11/26 15:15:44 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_eat(t_philo *philo)
{
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->stop_mutex);
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

void	print_status(t_philo *philo, char *str)
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
