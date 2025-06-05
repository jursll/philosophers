/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:37:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/05 17:15:15 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_simulation *sim, t_philosopher *philos)
{
	int		i;
	long	last;

	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		last = philos[i].last_meal_time;
		pthread_mutex_unlock(&sim->mtx_data);
		if (get_time_in_ms() - last > sim->time_to_die)
		{
			pthread_mutex_lock(&sim->mtx_print);
			printf("%ld %d died\n", get_time_in_ms() - sim->start_time, philos[i].id);
			pthread_mutex_unlock(&sim->mtx_print);
			pthread_mutex_lock(&sim->mtx_data);
			sim->simulation_end = 1;
			pthread_mutex_unlock(&sim->mtx_data);
			return (1);
		}
		i++;
	}
	return (0);
}

static int check_meals(t_simulation *sim, t_philosopher *philos)
{
	int	i;
	int	meals_count;

	if (sim->nb_meals == -1)
		return (0);
	meals_count = 0;
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		int eaten = philos[i].nb_meals_eaten;
		pthread_mutex_unlock(&sim->mtx_data);

		if (eaten >= sim->nb_meals)
			meals_count++;
		i++;
	}
	if (meals_count == sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		sim->simulation_end = 1;
		pthread_mutex_unlock(&sim->mtx_data);
		return (1);
	}
	return (0);
}

void *monitor_routine(void *arg)
{
	t_monitor		*mon;
	t_simulation	*sim;
	t_philosopher	*philos;

	mon = (t_monitor *)arg;
	sim = mon->sim;
	philos = mon->philos;
	while (1)
	{
		if (check_death(sim, philos))
			break;
		if (check_meals(sim, philos))
			break;
		usleep(500);
	}
	return (NULL);
}
