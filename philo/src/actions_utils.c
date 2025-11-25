/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:27 by anfiorit          #+#    #+#             */
/*   Updated: 2025/11/25 19:46:49 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	all_philos_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	check_meals_eaten(t_data *data)
{
	if (data->must_eat == -1)
		return (0);
	pthread_mutex_lock(&data->stop_mutex);
	if (all_philos_ate_enough(data))
	{
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_meals_eaten(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < data->nb_philos)
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
			return (1);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		i++;
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
