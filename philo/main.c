/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 18:24:05 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;
	t_philosopher	*philo;
	int				i;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./%s nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]\n", av[0]);
		return (1);
	}
	if (check_inits(&sim, &philo, ac, av))
		return (1);
/*
	printf("Simulation and philosphers initialized successfully\n");
	printf("Numbers of philosophers: %d\n", sim.nb_philos);
	printf("Time to die: %ld\n", sim.time_to_die);
	printf("Time to eat: %ld\n", sim.time_to_eat);
	printf("Time to sleep: %ld\n", sim.time_to_sleep);
	if (sim.nb_meals != -1)
		printf("Number of meals: %d\n", sim.nb_meals);
	else
		printf("Number of meals: illimited\n");
*/
	i = 0;
	while (i < sim.nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]))
		{
			printf("Error\nFailed to create thread for philosopher %d\n", i + 1);
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
