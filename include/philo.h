/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:01:54 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/23 16:36:50 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define YELLOW_TEXT "\x1B[33m"
#define RESET_TEXT "\x1B[0m"

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
	pthread_mutex_t	*forks;
	long			last_time_eat;
}	t_philo;

// time management
long	get_time_in_ms();
int		wait_or_die(int time_to_wait, t_philo *philo);

// Philo action
void	*philo_routine(void *arg);

#endif
