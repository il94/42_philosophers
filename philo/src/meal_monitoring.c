/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:47:45 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/19 22:01:59 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	unset_has_eaten(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->number_of_philosophers)
	{
		philo[i].has_eaten = FALSE;
		i++;
	}
}

static int	all_philos_has_eaten(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->number_of_philosophers)
	{
		if (!philo[i].has_eaten)
			return (0);
		i++;
	}
	return (1);
}

static int	monitoring_meal_count(t_arg *args)
{
	pthread_mutex_lock(&args->check_has_eaten);
	if (all_philos_has_eaten(args->philos))
	{
		args->meal_counter++;
		unset_has_eaten(args->philos);
	}
	if (args->meal_counter >= args->max_meals)
	{
		pthread_mutex_unlock(&args->check_has_eaten);
		return (1);
	}
	pthread_mutex_unlock(&args->check_has_eaten);
	return (0);
}

static int	monitoring_philos_state(t_arg *args)
{
	static int	i;

	pthread_mutex_lock(&args->check_last_meal);
	if (get_timestamp(args->start_meal) - args->philos[i].last_meal
		> args->time_to_die)
	{
		secure_print_log(args, args->philos[i].id, LOG_DIE);
		pthread_mutex_unlock(&args->check_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&args->check_last_meal);
	i++;
	if (i >= args->number_of_philosophers)
		i = 0;
	return (0);
}

void	*meal_monitoring(void *arg)
{
	t_arg	*args;

	args = (t_arg *)arg;
	while (1)
	{
		if (args->max_meals_mode && monitoring_meal_count(args))
			break ;
		else if (monitoring_philos_state(args))
			break ;
	}
	secure_set_end_meal(args);
	return (NULL);
}
