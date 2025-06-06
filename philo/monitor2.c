/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:09:19 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/06 15:49:10 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	current_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static long	compute_next_death_time(t_simulation *sim, t_philosopher *philos)
{
	int		i;
	long	next_death;
	long	last_meal;
	long	candidate;

	i = 0;
	next_death = LONG_MAX;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		last_meal = philos[i].last_meal_time;
		pthread_mutex_unlock(&sim->mtx_data);
		candidate = last_meal + sim->time_to_die;
		if (candidate < next_death)
			next_death = candidate;
		i++;
	}
	return next_death;
}

static int	check_death(t_simulation *sim, t_philosopher *philos)
{
	int		i;
	long	now;
	long	last_meal;

	now = current_time_ms();
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		last_meal = philos[i].last_meal_time;
		pthread_mutex_unlock(&sim->mtx_data);
		if ((now - last_meal) >= sim->time_to_die)
		{
			pthread_mutex_lock(&sim->mtx_print);
			printf("%ld %d died\n", now - sim->start_time, philos[i].id);
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

static int	check_meals(t_simulation *sim, t_philosopher *philos)
{
	int	i;
	int	count_ok = 0;
	int	eaten;

	count_ok = 0;
	if (sim->nb_meals < 0)
		return (0);
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		eaten = philos[i].nb_meals_eaten;
		pthread_mutex_unlock(&sim->mtx_data);
		if (eaten >= sim->nb_meals)
			count_ok++;
		i++;
	}
	if (count_ok == sim->nb_philos)
	{
		pthread_mutex_lock(&sim->mtx_data);
		sim->simulation_end = 1;
		pthread_mutex_unlock(&sim->mtx_data);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor		*mon;
	t_simulation	*sim;
	t_philosopher	*philos;
	long			now;
	long			next_death;
	long 			sleep_ms;

	mon = (t_monitor *)arg;
	sim = mon->sim;
	philos = mon->philos;
	while (1)
	{
		pthread_mutex_lock(&sim->mtx_data);
		if (sim->simulation_end)
		{
			pthread_mutex_unlock(&sim->mtx_data);
			break ;
		}
		pthread_mutex_unlock(&sim->mtx_data);
		next_death = compute_next_death_time(sim, philos);
		if (next_death == LONG_MAX)
			break ;
		now = current_time_ms();
		if (next_death <= now)
		{
			if (check_death(sim, philos))
				break ;
			continue ;
		}
		{
			sleep_ms = next_death - now - 1;
			if (sleep_ms > 0)
				usleep(sleep_ms * 1000);
		}
		if (check_death(sim, philos))
			break ;
		if (check_meals(sim, philos))
			break ;
	}
	return (NULL);
}
