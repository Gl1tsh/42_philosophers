/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:53:39 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/29 16:15:40 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

/**
 ** Check si le nombre de philo est paire ou impaire
 ** Les paires prennent la fouchette de droite, puis la gauche
 ** Les paires prennent la fouchette de gauche, puis la droite
 ** Pourquoi ? eviter les deadlocks
 ** Les nombreux sont la pour rendre les fourchettes si le philo meurt
 **/
int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_one_fork(philo, philo->id % philo->number_of_philo) != 0)
			return (1);
		if (take_one_fork(philo, philo->id - 1) != 0)
		{
			pthread_mutex_unlock(&philo->forks[philo->id
				% philo->number_of_philo]);
			return (1);
		}
	}
	else
	{
		if (take_one_fork(philo, philo->id - 1) != 0)
			return (1);
		if (take_one_fork(philo, philo->id % philo->number_of_philo) != 0)
		{
			pthread_mutex_unlock(&philo->forks[philo->id - 1]);
			return (1);
		}
	}
	return (0);
}

/**
 ** 1. le philo prend 2 fourchettes
 ** 2. print quand il mange
 ** 3. mange le temps qu'il doit (argv)
 ** 4. eaten++ (annonce combien de fois il a manger une fois de plus)
 ** 5. Rendre les fourchettes pour les autres philo
 ** return = savoir si il est pas mort
**/
int	eat(t_philo *philo)
{
	int	wait_should_die;

	if (take_forks(philo))
		return (1);
	printf("%ld %d is %seating%s\n", get_time_in_ms(), philo->id, YXT, RXT);
	philo->last_time_eat = get_time_in_ms();
	wait_should_die = wait_or_die(philo->time_to_eat, philo);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->forks[philo->id % philo->number_of_philo]);
	pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	return (wait_should_die);
}

int	nap(t_philo *philo)
{
	printf("%ld %d is %ssleeping%s\n", get_time_in_ms(), philo->id, GXT, RXT);
	return (wait_or_die(philo->time_to_sleep, philo));
}

/**
 ** Petite pause en pansant pour que le philo actuel ne reprenne pas les
 **	fourchettes tout de suite.
 ** (Laisse les autres prendre les fouchettes)
 **/
int	think(t_philo *philo)
{
	printf("%ld %d is %sthinking%s\n", get_time_in_ms(), philo->id, GXT, RXT);
	return (wait_or_die(2, philo));
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	philo->last_time_eat = get_time_in_ms();
	while (1)
	{
		if (eat(philo))
			return (NULL);
		if (philo->times_must_eat != 0
			&& philo->times_eaten >= philo->times_must_eat)
			break ;
		if (nap(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
	return (NULL);
}
