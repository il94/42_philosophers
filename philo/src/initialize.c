/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:41:58 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/12 15:44:42 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_philo	*initialize_philo_struct(t_arg args)
{
	t_philo	*philos;
	int	i;

	philos = malloc(sizeof(t_philo) * args.number_of_philosophers);
	if (!philos)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		// if (pthread_mutex_init(&philos[i].fork, NULL))
		// 	free and exit
		pthread_mutex_lock(&philos[i].fork);
		i++;
	}	
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
		args.number_of_times_each_philosopher_must_eat = ft_long_long_atoi(parameters[4]);
	else
		args.number_of_times_each_philosopher_must_eat = 0;
	return (args);
}

void	initialize_structs(t_arg *args, t_philo **philos, char **parameters)
{
	*args = initialize_arg_struct(parameters);
	*philos = initialize_philo_struct(*args);
}