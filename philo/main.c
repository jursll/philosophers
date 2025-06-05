/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/05 12:12:02 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_simulation *sim, t_philosopher *philo,
							pthread_t *monitor_thread, t_monitor *mon)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philosopher_routine, &philo[i]))
		{
			printf("Error\nFailed to create thread for philo %d\n", i + 1);
			while (i-- > 0)
				pthread_join(philo[i].thread, NULL);
			return (1);
		}
		i++;
	}
	mon->sim = sim;
	mon->philos = philo;
	if (pthread_create(monitor_thread, NULL, monitor_routine, mon))
	{
		printf("Error\nFailed to create monitor thread\n");
		return (1);
	}
	return (0);
}

static void	join_threads(t_simulation *sim, t_philosopher *philo,
							pthread_t monitor_thread)
{
	int	i;

	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

static void	cleanup_ressources(t_simulation *sim, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->mtx_print);
	pthread_mutex_destroy(&sim->mtx_data);
	free(sim->forks);
	free(philo);
}

int	main(int ac, char **av)
{
	t_monitor		mon;
	t_simulation	sim;
	t_philosopher	*philo;
	pthread_t		monitor_thread;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./%s nb_philos die eat sleep [nb_meals]\n", av[0]);
		return (1);
	}
	if (check_inits(&sim, &philo, ac, av))
		return (1);
	if (start_threads(&sim, philo, &monitor_thread, &mon))
	{
		cleanup_ressources(&sim, philo);
		return (1);
	}
	join_threads(&sim, philo, monitor_thread);
	cleanup_ressources(&sim, philo);
	return (0);
}
