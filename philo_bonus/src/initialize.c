/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:41:58 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/19 21:25:46 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	return (philos);
}

static void	open_semaphores(t_arg *args)
{
	sem_unlink("/forks");
	sem_unlink("/logs");
	args->forks = sem_open("/forks", O_CREAT, 0644, args->number_of_philosophers);
	args->logs = sem_open("/logs", O_CREAT, 0644, 1);
}

static t_arg	initialize_arg_struct(char **parameters)
{
	t_arg	args;

	args.number_of_philosophers = ft_long_long_atoi(parameters[0]);
	args.time_to_die = ft_long_long_atoi(parameters[1]);
	args.time_to_eat = ft_long_long_atoi(parameters[2]);
	args.time_to_sleep = ft_long_long_atoi(parameters[3]);
	args.time_to_think = args.time_to_die;
	args.max_meals_mode = FALSE;
	if (parameters[4])
	{
		args.max_meals_mode = TRUE;
		args.max_meals = ft_long_long_atoi(parameters[4]);
	}
	gettimeofday(&args.start_meal, NULL);
	open_semaphores(&args);
	args.end_meal = FALSE;
	args.meal_counter = 0;
	return (args);
}

void	initialize_struct(t_arg *args, t_philo **philos, char **parameters)
{
	*args = initialize_arg_struct(parameters);
	*philos = initialize_philo_struct(args);
	args->philos = *philos;
}
