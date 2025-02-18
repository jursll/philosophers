/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:57:05 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/07 10:53:38 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct		s_simulation
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	*forks;
	int				simulation_end;
}					t_simulation;

typedef struct 		s_philosopher
{
	int				id;
	int				nb_meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_simulation	*sim;
	pthread_t		thread;
}					t_philosopher;

int		init_simulation_variables(t_simulation *sim, int ac, char **av);
int		init_simulation_mutex(t_simulation *sim);
int		init_forks_mutex(t_simulation *sim);

long	get_time_in_ms(void);

#endif
