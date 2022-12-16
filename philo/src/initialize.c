/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:41:58 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/16 19:05:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_philo	*initialize_philo_struct(t_arg *args)
{
	t_philo	*philos;
	int	i;

	philos = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philos)
		exit (EXIT_FAILURE);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (!args->forks)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].id = i;		
		philos[i].args = args;
		philos[i].is_eating = FALSE;
		philos[i].is_thinking = FALSE;
		philos[i].is_sleeping = FALSE;
		pthread_mutex_init(&args->forks[i], NULL);
		philos[i].last_meal = 0;
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].left_fork = &args->forks[i];
		if (i > 0)
			philos[i].right_fork = &args->forks[i - 1];
		i++;
	}
	philos[0].right_fork = &args->forks[args->number_of_philosophers - 1];
	return (philos);
}

static t_arg	initialize_arg_struct(char **parameters)
{
	t_arg	args;

	args.number_of_philosophers = ft_long_long_atoi(parameters[0]);
	args.time_to_die = ft_long_long_atoi(parameters[1]);
	args.time_to_eat = ft_long_long_atoi(parameters[2]);
	args.time_to_sleep = ft_long_long_atoi(parameters[3]);
	if (parameters[4])
	{
		args.number_of_times_each_philosopher_must_eat = ft_long_long_atoi(parameters[4]);
		args.count_meals_number = TRUE;
	}
	else
	{
		args.number_of_times_each_philosopher_must_eat = 0;
		args.count_meals_number = FALSE;
	}
	pthread_mutex_init(&args.print, NULL);
	args.philo_is_alive = TRUE;
	return (args);
}

void	initialize_structs(t_arg *args, t_philo **philos, char **parameters)
{
	*args = initialize_arg_struct(parameters);
	*philos = initialize_philo_struct(args);
	args->philos = *philos;
}