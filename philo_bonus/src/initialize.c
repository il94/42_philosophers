/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:41:58 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/02 15:56:18 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_philo	*initialize_philo_struct(t_arg *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philos)
		free_memory(args, EXIT);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].pid = 1;
		philos[i].has_eaten = FALSE;
		philos[i].last_meal = 0;
		philos[i].args = args;
		i++;
	}
	return (philos);
}

static void	open_semaphores(t_arg *args)
{
	sem_unlink("/process");
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/lock_print_log");
	sem_unlink("/check_last_meal");
	sem_unlink("/check_has_eaten");
	args->process = sem_open("/process", O_CREAT, 0644, 1);
	args->death = sem_open("/death", O_CREAT, 0644, 1);
	args->forks = sem_open("/forks", O_CREAT, 0644,
			args->number_of_philosophers);
	args->lock_print_log = sem_open("/lock_print_log", O_CREAT, 0644, 1);
	args->check_last_meal = sem_open("/check_last_meal", O_CREAT, 0644, 1);
	args->check_has_eaten = sem_open("/check_has_eaten", O_CREAT, 0644, 1);
	if (args->process == SEM_FAILED || args->death == SEM_FAILED
		|| args->forks == SEM_FAILED  || args->lock_print_log == SEM_FAILED
		|| args->check_last_meal == SEM_FAILED
		|| args->check_has_eaten == SEM_FAILED)
		free_memory(args, EXIT);
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
	open_semaphores(&args);
	args.meal_counter = 0;
	return (args);
}

void	initialize_struct(t_arg *args, char **parameters)
{
	*args = initialize_arg_struct(parameters);
	args->philos = initialize_philo_struct(args);
}
