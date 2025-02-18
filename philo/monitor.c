/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:37:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 20:18:02 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_simulation *sim, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if ((get_time_in_ms() - philos[i].last_meal_time)
			> sim->time_to_die)
		{
			print_message(sim, philos[i].id, "died\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_meals(t_simulation *sim, t_philosopher *philos)
{
	int	i;
	int	meals_count;

	if (sim->nb_meals == -1)
		return (0);
	meals_count = 0;
	i = 0;
	while (i < sim->nb_philos)
	{
		if (philos[i].nb_meals_eaten >= sim->nb_meals)
			meals_count++;
		i++;
	}
	if (meals_count == sim->nb_philos)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor		*mon;
	t_simulation	*sim;
	t_philosopher	*philos;

	mon = (t_monitor *)arg;
	sim = mon->sim;
	philos = mon->philos;
	while (!sim->simulation_end)
	{
		if (check_death(sim, philos))
		{
			sim->simulation_end = 1;
			return (NULL);
		}
		if (check_meals(sim, philos))
		{
			sim->simulation_end = 1;
			return (NULL);
		}
		usleep (1000);
	}
	return (NULL);
}
