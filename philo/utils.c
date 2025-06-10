/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:03 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/10 14:09:04 by julrusse         ###   ########.fr       */
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

	if (str == NULL || *str == '\0')
		return (0);
	if (str[0] == '+')
		i = 1;
	else if (str[0] == '-')
		return (0);
	else
		i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
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

void	sleep_with_checks(t_simulation *sim, long sleep_time_ms)
{
	long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < sleep_time_ms)
	{
		pthread_mutex_lock(&sim->mtx_data);
		if (sim->simulation_end)
		{
			pthread_mutex_unlock(&sim->mtx_data);
			return ;
		}
		pthread_mutex_unlock(&sim->mtx_data);
		usleep(150);
	}
}
//valgrind --tool=helgrind --fair-sched=yes
