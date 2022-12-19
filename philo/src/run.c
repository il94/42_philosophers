/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/19 20:50:08 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	destroy_all_mutex(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			free_all_and_exit(args);
		i++;
	}
	if (pthread_mutex_destroy(&args->lock_print_log) != 0)
		free_all_and_exit(args);
	if (pthread_mutex_destroy(&args->check_end_meal) != 0)
		free_all_and_exit(args);
	if (pthread_mutex_destroy(&args->check_last_meal) != 0)
		free_all_and_exit(args);
	if (pthread_mutex_destroy(&args->check_has_eaten) != 0)
		free_all_and_exit(args);
}

static void	join_all_threads(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			free_all_and_exit(args);
		i++;
	}
	if (pthread_join(args->meal_thread, NULL) != 0)
		free_all_and_exit(args);
}

static void	create_all_threads(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_create(&args->meal_thread, NULL, meal_monitoring, args) != 0)
		free_all_and_exit(args);
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, meal_time, &philos[i]) != 0)
			free_all_and_exit(args);
		i++;
	}
}

void	run(t_arg *args, t_philo *philos)
{
	create_all_threads(args, philos);
	join_all_threads(args, philos);
	destroy_all_mutex(args);
}
