/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fio <fio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:12:48 by fio               #+#    #+#             */
/*   Updated: 2025/11/22 14:01:20 by fio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void init_data(t_data *data, int *tab, int ac)
{
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if(ac == 6)
		data->must_eat = tab[4];
	else
		data->must_eat = -1;
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
		data->philos[i].data = data;
		i++;
	}	
}