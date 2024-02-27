/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:01:54 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/27 20:29:25 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/**
 ** RED
 ** GREEN
 ** YELLOW
 ** RESET
 **/
# define RYT "\x1B[31m"
# define GXT "\x1B[32m"
# define YXT "\x1B[33m"
# define RXT "\x1B[0m"

// struct pre-declaration
struct	s_table;

// struct about time
typedef struct s_philo
{
	int				id;
	int				number_of_philo;
	pthread_t		thread_id;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_die;
	int				times_eaten;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	long			last_time_eat;
	struct s_table	*table;
}	t_philo;

// struct philo data
typedef struct s_table
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				times_must_eat;
	int				stop;
	pthread_mutex_t	*forks;
	t_philo			*philos;	
}	t_table;

// time management
long	get_time_in_ms(void);
int		wait_or_die(int time_to_wait, t_philo *philo);

// Philo action
void	*philo_routine(void *arg);

int		ft_atoi_custom(const char *str);

#endif
