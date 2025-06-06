/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:47:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/06 13:33:46 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo, t_simulation *sim)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(sim, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(sim, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(sim, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(sim, philo->id, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	print_message(t_simulation *sim, int id, const char *msg)
{
	long	time;

	pthread_mutex_lock(&sim->mtx_data);
	if (sim->simulation_end)
	{
		if (ft_strcmp(msg, "died\n") != 0)
		{
			pthread_mutex_unlock(&sim->mtx_data);
			return ;
		}
	}
	pthread_mutex_unlock(&sim->mtx_data);
	pthread_mutex_lock(&sim->mtx_print);
	time = get_time_in_ms() - sim->start_time;
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&sim->mtx_print);
}
