/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/18 00:10:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*check_end(void *strouct)
{
	t_arg	*args;
	int		i;

	args = (t_arg *)strouct;
	i = 0;
	while (1)
	{
		// pthread_mutex_lock(&args->check_last_meal);
		if (get_timestamp(args->meal_time) - args->philos[i].last_meal > args->time_to_die)
		{
			print_log(args, args->philos[i].id, LOG_DIE);
			break ;
		}
		// pthread_mutex_unlock(&args->check_last_meal);
		i++;
		if (i >= args->number_of_philosophers)
			i = 0;
	}
	// pthread_mutex_lock(&args->check_philo_life);
	pthread_mutex_lock(&args->check_philo_life2);
	args->end_meal = TRUE;
	pthread_mutex_unlock(&args->check_philo_life2);
	// pthread_mutex_unlock(&args->check_philo_life);
	return (NULL);
}

void	run(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_create(&args->meal_thread, NULL, check_end, args);
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, meal_time, &philos[i]))
			exit (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL))
			exit (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(args->meal_thread, NULL))
		exit (EXIT_FAILURE);
}
