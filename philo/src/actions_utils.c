/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfiorit <anfiorit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:41:27 by anfiorit          #+#    #+#             */
/*   Updated: 2025/11/24 17:41:28 by anfiorit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philosophers.h"

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
