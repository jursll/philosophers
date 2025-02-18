/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:47:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:08 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_simulation	*sim;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(100);
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
		sleep_with_checks(sim, sim->time_to_eat);
		philo->nb_meals_eaten++;
		// let fork
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// check if done
		if (sim->simulation_end)
			break;
		// sleep
		print_message(sim, philo->id, "is sleeping\n");
		sleep_with_checks(sim, sim->time_to_sleep);
		// check if done
		if (sim->simulation_end)
			break;
		// think
		print_message(sim, philo->id, "is thinking\n");
		usleep(100); /*optional*/
	}
	return (NULL);
}
