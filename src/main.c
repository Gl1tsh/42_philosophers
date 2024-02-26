/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:30:24 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/27 00:26:11 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

/**
 **	Allocation pour le nombre de philosopher
 **	Allocation pour le nombre de fourchette
 **	Creation de fourchettes pour philo
 **/
int	table_prepare(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	if (table->philos == NULL)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (table->forks == NULL)
		return (1);
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (0);
}

// Creation de chaque chaque thread philosopher
int	philo_launcher(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].number_of_philo = table->number_of_philo;
		table->philos[i].forks = table->forks;
		table->philos[i].time_to_eat = 200;
		table->philos[i].time_to_sleep = 800;
		table->philos[i].time_to_think = 800;
		table->philos[i].time_to_die = 2300;
		pthread_create(&table->philos[i].thread_id, NULL, philo_routine,
			&table->philos[i]);
		i++;
	}
	return (0);
}

int	table_clean(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	while (i < table->number_of_philo)
	{
		err = pthread_join(table->philos[i].thread_id, NULL);
		if (err != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < table->number_of_philo)
	{
		err = pthread_mutex_destroy(&table->forks[i]);
		if (err != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	table->number_of_philo = ft_atoi_custom(argv[1]);
	if (table->number_of_philo < 1)
		return (-1);
	table->time_to_die = ft_atoi_custom(argv[2]);
	table->time_to_eat = ft_atoi_custom(argv[3]);
	table->time_to_sleep = ft_atoi_custom(argv[4]);
	if (argc == 6)
		table->eat_count = ft_atoi_custom(argv[5]);
	else
		table->eat_count = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (init_table(argc, argv, &table) != 0)
		return (1);
	if (table_prepare(&table) != 0)
		return (1);
	philo_launcher(&table);
	table_clean(&table);
	return (0);
}
