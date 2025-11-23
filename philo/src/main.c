/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fio <fio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:18 by anfiorit          #+#    #+#             */
/*   Updated: 2025/11/22 14:02:28 by fio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	int		*tab;
	if(ac != 5 && ac != 6)
	{
		printf("Nombre d'arguments invalide\n");
		return(1);
	}
	tab = convert_into_int(ac, av);
	if(tab == NULL)
	{
		printf("Les arguments doivent etres des nombres positifs\n");
		return(1);
	}
	t_data data;
	init_data(&data, tab, ac);
		return (0);
}

int	*convert_into_int(int ac, char **av)
{
	int		*tab;
	int		i;

	i = 0;
	tab = malloc (sizeof(int) * ac - 1);
	if(tab == NULL)
		return(NULL);
	while(i < ac - 1)
	{
		tab[i] = ft_atoi(av[i + 1]);
		if(tab[i] <= 0)
		{
			free(tab);
			return (NULL);
		}
		i++;
	}
	return(tab);
}
