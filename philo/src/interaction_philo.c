/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:54:32 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/18 00:45:15 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	think_deeply(t_philo *philo)
{
	print_log(philo->args, philo->id, LOG_THINK);
}

void	go_to_bed(t_philo *philo)
{
	print_log(philo->args, philo->id, LOG_SLEEP);
	usleep(philo->args->time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_log(philo->args, philo->id, LOG_EAT);
	usleep(philo->args->time_to_eat * 1000);
	drop_forks(philo);
	// pthread_mutex_lock(&philo->args->check_last_meal);
	// if (philo->args->end_meal)
	philo->last_meal = get_timestamp(philo->args->meal_time);
	// pthread_mutex_unlock(&philo->args->check_last_meal);
}

void	*meal_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(10);
	// pthread_mutex_lock(&philo->args->check_philo_life2);
	// while (!philo->args->end_meal
	// 	&& philo->args->meal_counter <= philo->args->max_meals)
	// pthread_mutex_lock(&philo->args->check_philo_life2);
	while (1)
	{
		pthread_mutex_lock(&philo->args->check_philo_life2);
		if (philo->args->end_meal)
		{
			pthread_mutex_unlock(&philo->args->check_philo_life2);		
			break ;
		}
		pthread_mutex_unlock(&philo->args->check_philo_life2);
		eat(philo);
		go_to_bed(philo);
		think_deeply(philo);
		// if (philo->args->count_max_meals == TRUE)
		// 	philo->args->meal_counter += 1;
		usleep(500);
	}
	// pthread_mutex_lock(&philo->args->check_philo_life2);
	return (NULL);
}
