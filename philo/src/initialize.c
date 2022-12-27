/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:41:58 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/27 17:25:07 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	assigning_fork_addresses(t_philo *philos, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].left_fork = &args->forks[i];
		if (i > 0)
			philos[i].right_fork = &args->forks[i - 1];
		i++;
	}
	philos[0].right_fork = &args->forks[args->number_of_philosophers - 1];
}

static t_philo	*initialize_philo_struct(t_arg *args)
{
	t_philo	*philos;
	int		i;

	philos = NULL;
	philos = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philos)
		free_all_and_exit(args);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].has_eaten = FALSE;
		philos[i].last_meal = 0;
		philos[i].args = args;
		i++;
	}
	assigning_fork_addresses(philos, args);
	return (philos);
}

static void	init_all_mutex(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->lock_print_log, NULL);
	pthread_mutex_init(&args->check_end_meal, NULL);
	pthread_mutex_init(&args->check_last_meal, NULL);
	pthread_mutex_init(&args->check_has_eaten, NULL);
}

static t_arg	initialize_arg_struct(char **parameters)
{
	t_arg	args;

	args.number_of_philosophers = ft_long_long_atoi(parameters[0]);
	args.time_to_die = ft_long_long_atoi(parameters[1]);
	args.time_to_eat = ft_long_long_atoi(parameters[2]);
	args.time_to_sleep = ft_long_long_atoi(parameters[3]);
	args.time_to_think = args.time_to_eat;
	args.max_meals_mode = FALSE;
	if (parameters[4])
	{
		args.max_meals_mode = TRUE;
		args.max_meals = ft_long_long_atoi(parameters[4]);
	}
	gettimeofday(&args.start_meal, NULL);
	args.forks = malloc(sizeof(pthread_mutex_t) * args.number_of_philosophers);
	if (!args.forks)
		exit (EXIT_FAILURE);
	init_all_mutex(&args);
	args.end_meal = FALSE;
	args.meal_counter = 0;
	return (args);
}

void	initialize_struct(t_arg *args, char **parameters)
{
	*args = initialize_arg_struct(parameters);
	args->philos = initialize_philo_struct(args);
}
