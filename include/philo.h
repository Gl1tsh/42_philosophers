/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:01:54 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/23 14:02:13 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// struct about time
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	int			time_to_eat;	
	int			time_to_sleep;
	int			time_to_think;
	int			time_to_die;
}	t_philo;

// time management
long	get_time_in_ms();

// Philo action
void	*philo_routine(void *arg);

#endif
