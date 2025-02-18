/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:47:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 19:11:46 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_simulation	*sim;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	while (!sim->simulation_end)
	{
		// take forks
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_message(sim, philo->id, "has taken a fork\n");
			pthread_mutex_lock(philo->right_fork);
			print_message(sim, philo->id, "has taken a fork\n");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_message(sim, philo->id, "has taken a fork\n");
			pthread_mutex_lock(philo->left_fork);
			print_message(sim, philo->id, "has taken a fork\n");
		}
		// eat
		philo->last_meal_time = get_time_in_ms();
		print_message(sim, philo->id, "is eating\n");
		usleep(sim->time_to_eat * 1000);
		philo->nb_meals_eaten++;
		// let fork
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// sleep
		print_message(sim, philo->id, "is sleeping\n");
		usleep(sim->time_to_sleep * 1000);
		// think
		print_message(sim, philo->id, "is thinking\n");
		usleep(100); /*optional*/
	}
	return (NULL);
}
