/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:03 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 15:53:46 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isstrnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			ms;

	if (gettimeofday(&tv, NULL))
		return (0);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}
