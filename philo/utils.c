/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:03 by julrusse          #+#    #+#             */
/*   Updated: 2025/05/30 15:09:01 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	return (result * sign);
}

int	ft_isstrnum(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
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

void	print_message(t_simulation *sim, int id, const char *msg)
{
	long	time;

	pthread_mutex_lock(&sim->mtx_print);
	time = get_time_in_ms() - sim->start_time;
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&sim->mtx_print);
}

void	sleep_with_checks(t_simulation *sim, long sleep_time_ms)
{
	long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < sleep_time_ms)
	{
		if (sim->simulation_end)
			break ;
		usleep(150);
	}
}
