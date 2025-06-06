/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/06 14:32:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation_variables(t_simulation *sim, int ac, char **av)
{
	sim->nb_philos = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		sim->nb_meals = ft_atoi(av[5]);
	else
		sim->nb_meals = -1;
	sim->simulation_end = 0;
	sim->start_time = get_time_in_ms();
	if (sim->nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(sim->time_to_die * 1000);
		printf("%ld 1 died\n", get_time_in_ms() - sim->start_time);
		sim->simulation_end = 1;
		return (1);
	}
	if (sim->nb_philos < 0)
		return (printf("Error:\nNumber of philosophers must be positive\n"), 1);
	if (sim->nb_philos == 0)
		return (printf("Error:\nThere must be at least 1 philosopher\n"), 1);
	return (0);
}

int	init_simulation_mutex(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->mtx_print, NULL))
	{
		printf("Error:\nPrint Mutex initialisation failed\n");
		return (1);
	}
	if (pthread_mutex_init(&sim->mtx_data, NULL))
	{
		printf("Error:\nData Mutex initialisation failed\n");
		pthread_mutex_destroy(&sim->mtx_print);
		return (1);
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philos);
	if (!sim->forks)
	{
		printf("Error:\nMemory allocation for forks failed\n");
		pthread_mutex_destroy(&sim->mtx_print);
		pthread_mutex_destroy(&sim->mtx_data);
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
			pthread_mutex_destroy(&sim->mtx_data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_simulation *sim, t_philosopher **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philosopher) * sim->nb_philos);
	if (!*philo)
	{
		printf("Memory allocation for philosophers failed");
		return (1);
	}
	while (i < sim->nb_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].nb_meals_eaten = 0;
		(*philo)[i].last_meal_time = sim->start_time;
		(*philo)[i].sim = sim;
		(*philo)[i].right_fork = &sim->forks[i];
		if (i == 0)
			(*philo)[i].left_fork = &sim->forks[sim->nb_philos - 1];
		else
			(*philo)[i].left_fork = &sim->forks[i - 1];
		i++;
	}
	return (0);
}

int	check_inits(t_simulation *sim, t_philosopher **philo, int ac, char **av)
{
	if (!ft_isstrnum(av[1]) || !ft_isstrnum(av[2])
		|| !ft_isstrnum(av[3]) || !ft_isstrnum(av[4]))
	{
		printf("Error\nArguments must be non-negative integer\n");
		return (1);
	}
	if (ac == 6 && !ft_isstrnum(av[5]))
	{
		printf("Error\nArguments must be non-negative integer\n");
		return (1);
	}
	if (init_simulation_variables(sim, ac, av))
		return (1);
	if (init_simulation_mutex(sim))
		return (1);
	if (init_forks_mutex(sim))
		return (1);
	if (init_philosophers(sim, philo))
		return (1);
	return (0);
}
