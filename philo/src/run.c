/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/04 14:56:56 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	create_all_threads(t_arg *args)
{
	int	i;

	i = 0;
	if (pthread_create(&args->meal_thread, NULL, meal_monitoring, args) != 0)
		free_memory(args, EXIT);
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&args->philos[i].thread, NULL, meal_time,
				&args->philos[i]) != 0)
			free_memory(args, EXIT);
		i++;
	}
}

static void	join_all_threads(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(args->philos[i].thread, NULL) != 0)
			free_memory(args, EXIT);
		i++;
	}
	if (pthread_join(args->meal_thread, NULL) != 0)
		free_memory(args, EXIT);
}

static void	destroy_all_mutex(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->lock_print_log);
	pthread_mutex_destroy(&args->check_end_meal);
	pthread_mutex_destroy(&args->check_last_meal);
	if (args->max_meals_mode)
		pthread_mutex_destroy(&args->check_has_eaten);
}

void	free_memory(t_arg *args, t_exit exit_bool)
{
	destroy_all_mutex(args);
	if (args->forks)
		free(args->forks);
	if (args->philos)
		free(args->philos);
	if (exit_bool == EXIT)
		exit (EXIT_FAILURE);
}

void	run(t_arg *args)
{
	create_all_threads(args);
	join_all_threads(args);
	free_memory(args, CONTINUE);
}
