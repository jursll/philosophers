/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:47:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 20:07:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philosopher *philo, t_simulation *sim)
{
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
}

static void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

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
		take_forks(philo, sim);
		philo->last_meal_time = get_time_in_ms();
		print_message(sim, philo->id, "is eating\n");
		sleep_with_checks(sim, sim->time_to_eat);
		philo->nb_meals_eaten++;
		release_forks(philo);
		if (sim->simulation_end)
			break ;
		print_message(sim, philo->id, "is sleeping\n");
		sleep_with_checks(sim, sim->time_to_sleep);
		if (sim->simulation_end)
			break ;
		print_message(sim, philo->id, "is thinking\n");
		usleep(100);
	}
	return (NULL);
}
