/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/07 11:07:41 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation_variables(t_simulation *sim, int ac, char **av)
{
	sim->nb_philos = atoi(av[1]);
	if (sim->nb_philos == 1 || sim->nb_philos <= 0)
	{
		if (sim->nb_philos == 1)
			printf("Philosopher has only 1 fork and cannot eat: he died...\n");
		else
			printf("Error:\nInvalid number of philosophers\n");
		return (1);
	}
	sim->time_to_die = atoi(av[2]);
	sim->time_to_eat = atoi(av[3]);
	sim->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		sim->nb_meals = atoi(av[5]);
	else sim->nb_meals = -1;
	sim->simulation_end = 0;
	sim->start_time = get_time_in_ms();
	return (0);
}

int	init_simulation_mutex(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->mtx_print, NULL))
	{
		printf("Error:\nMutex initialisation failed\n");
		return (1);
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philos);
	if (!sim->forks)
	{
		printf("Error:\nMemory allocation for forks failed\n");
		pthread_mutex_destroy(&sim->mtx_print);
		return (1);
	}
	return (0);
}

int	init_forks_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
		{
			printf("Fork Mutex initialisation failed\n");
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&sim->forks[i]);
			}
			free (sim->forks);
			pthread_mutex_destroy(&sim->mtx_print);
			return (1);
		}
		i++;
	}
	return (0);
}
