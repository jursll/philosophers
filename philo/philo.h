/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:57:05 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/06 15:09:14 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_simulation
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_data;
	pthread_mutex_t	*forks;
	int				simulation_end;
}					t_simulation;

typedef struct s_philosopher
{
	int				id;
	int				nb_meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_simulation	*sim;
	pthread_t		thread;
}					t_philosopher;

typedef struct s_monitor
{
	t_simulation	*sim;
	t_philosopher	*philos;
}					t_monitor;

// UTILS
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isstrnum(char *str);
long	get_time_in_ms(void);
void	sleep_with_checks(t_simulation *sim, long sleep_time_ms);

// INIT
int		init_simulation_variables(t_simulation *sim, int ac, char **av);
int		init_simulation_mutex(t_simulation *sim);
int		init_forks_mutex(t_simulation *sim);
int		init_philosophers(t_simulation *sim, t_philosopher **philo);
int		check_inits(t_simulation *sim, t_philosopher **philo,
			int ac, char **av);

// PHILO
void	print_message(t_simulation *sim, int id, const char *msg);
void	take_forks(t_philosopher *philo, t_simulation *sim);
void	release_forks(t_philosopher *philo);
int		check_simulation_end(t_simulation *sim);
void	do_eat(t_philosopher *philo, t_simulation *sim);
void	do_sleep(t_philosopher *philo, t_simulation *sim);
void	do_think(t_philosopher *philo, t_simulation *sim);
void	*philosopher_routine(void *arg);

// MONITOR
void	*monitor_routine(void *arg);

#endif
