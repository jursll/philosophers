/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:37:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 19:55:34 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_monitor		*mon;
	t_simulation	*sim;
	t_philosopher	*philos;
	int				i;
	int				meals_count;

	mon = (t_monitor *)arg;
	sim = mon->sim;
	philos = mon->philos;
	while (!sim->simulation_end)
	{
		i = 0;
		while (i < sim->nb_philos)
		{
			if ((get_time_in_ms() - philos[i].last_meal_time)
				> sim->time_to_die)
			{
				print_message(sim, philos[i].id, "died\n");
				sim->simulation_end = 1;
				return (NULL);
			}
			i++;
		}
		if (sim->nb_meals != -1)
		{
			meals_count = 0;
			i = 0;
			while (i < sim->nb_philos)
			{
				if (philos[i].nb_meals_eaten >= sim->nb_meals)
					meals_count++;
				i++;
			}
			if (meals_count == sim->nb_philos)
			{
				sim->simulation_end = 1;
				return (NULL);
			}
		}
		usleep (1000);
	}
	return (NULL);
}
