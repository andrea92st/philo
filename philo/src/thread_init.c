/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:53:18 by fio               #+#    #+#             */
/*   Updated: 2025/11/25 15:38:43 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, routine,
                   &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor, data);
}

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		philo_eat(philo);
		philo_sleep(philo);
		philo_thinking(philo);		
	}
	return (NULL) ;
}

