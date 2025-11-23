/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fio <fio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:53:18 by fio               #+#    #+#             */
/*   Updated: 2025/11/23 13:30:47 by fio              ###   ########.fr       */
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
}

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *) arg;
	while(!is_dead(philo->data))
	{
		philo_eat();
		philo_sleep();
		philo_thinking();		
	}
}
