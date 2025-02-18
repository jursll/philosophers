/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 19:57:25 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_monitor		mon;
	t_simulation	sim;
	t_philosopher	*philo;
	pthread_t		monitor_thread;
	int				i;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./%s nb_philos die eat sleep [nb_meals]\n", av[0]);
		return (1);
	}
	if (check_inits(&sim, &philo, ac, av))
		return (1);
	i = 0;
	while (i < sim.nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philosopher_routine, &philo[i]))
		{
			printf("Error\nFailed to create thread for philo %d\n", i + 1);
			while (i-- > 0)
				pthread_join(philo[i].thread, NULL);
			i = 0;
			while (i < sim.nb_philos)
			{
				pthread_mutex_destroy(&sim.forks[i]);
				i++;
			}
			pthread_mutex_destroy(&sim.mtx_print);
			free(sim.forks);
			free(philo);
			return (1);
		}
		i++;
	}
	mon.sim = &sim;
	mon.philos = philo;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &mon))
	{
		printf("Error\nFailed to create monitor thread\n");
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < sim.nb_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < sim.nb_philos)
	{
		pthread_mutex_destroy(&sim.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim.mtx_print);
	free(sim.forks);
	free(philo);
	return (0);
}
