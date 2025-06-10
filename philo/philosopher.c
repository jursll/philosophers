/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:52:24 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/10 12:11:08 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_end(t_simulation *sim)
{
	int	ended;

	pthread_mutex_lock(&sim->mtx_data);
	ended = sim->simulation_end;
	pthread_mutex_unlock(&sim->mtx_data);
	return (ended);
}

void	do_eat(t_philosopher *philo, t_simulation *sim)
{
	take_forks(philo, sim);
	pthread_mutex_lock(&sim->mtx_data);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&sim->mtx_data);
	print_message(sim, philo->id, "is eating");
	sleep_with_checks(sim, sim->time_to_eat);
	pthread_mutex_lock(&sim->mtx_data);
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&sim->mtx_data);
	release_forks(philo);
}

void	do_sleep(t_philosopher *philo, t_simulation *sim)
{
	print_message(sim, philo->id, "is sleeping");
	sleep_with_checks(sim, sim->time_to_sleep);
}

void	do_think(t_philosopher *philo, t_simulation *sim)
{
	print_message(sim, philo->id, "is thinking");
	sleep_with_checks(sim, 1);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		sleep_with_checks(sim, 1);
	while (1)
	{
		if (check_simulation_end(sim))
			break ;
		do_eat(philo, sim);
		if (check_simulation_end(sim))
			break ;
		do_sleep(philo, sim);
		if (check_simulation_end(sim))
			break ;
		do_think(philo, sim);
	}
	return (NULL);
}
