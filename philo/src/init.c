/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:12:48 by fio               #+#    #+#             */
/*   Updated: 2025/11/24 18:14:41 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void init_data(t_data *data, int *tab, int ac)
{
	int		i;	
	
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if(ac == 6)
		data->must_eat = tab[4];
	else
		data->must_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = get_time();
	init_philo(data);
}

void	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc (sizeof(t_philo) * data->nb_philos);
	if(data->philos == NULL)
		return ;
	i = 0;
	while(i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philos;
		i++;
	}	
}
