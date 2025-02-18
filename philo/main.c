/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/18 16:21:49 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;
	t_philosopher	*philo;
//	int				i;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./%s nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]\n", av[0]);
		return (1);
	}
	if (check_inits(&sim, &philo, ac, av))
		return (1);

	printf("Simulation and philosphers initialized successfully\n");
	printf("Numbers of philosophers: %d\n", sim.nb_philos);
	printf("Time to die: %ld\n", sim.time_to_die);
	printf("Time to eat: %ld\n", sim.time_to_eat);
	printf("Time to sleep: %ld\n", sim.time_to_sleep);
	if (sim.nb_meals != -1)
		printf("Number of meals: %d\n", sim.nb_meals);
	else
		printf("Number of meals: illimited\n");

	return (0);
}
