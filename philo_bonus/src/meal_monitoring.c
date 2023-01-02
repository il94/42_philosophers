/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:47:45 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/27 16:58:37 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	monitoring_meal_count(t_philo *philo)
{
	sem_wait(philo->args->check_has_eaten);
	if (philo->has_eaten)
	{
		philo->args->meal_counter++;
		philo->has_eaten = FALSE;
	}
	if (philo->args->meal_counter >= philo->args->max_meals)
	{
		sem_post(philo->args->check_has_eaten);
		return (1);
	}
	sem_post(philo->args->check_has_eaten);
	return (0);
}

static int	monitoring_philos_state(t_philo *philo)
{
	sem_wait(philo->args->check_last_meal);
	if (get_timestamp(philo->args->start_meal) - philo->last_meal
		> philo->args->time_to_die)
	{
		secure_print_log(philo->args, philo->id, LOG_DIE);
		sem_post(philo->args->check_last_meal);
		return (1);
	}
	sem_post(philo->args->check_last_meal);
	return (0);
}

void	*meal_monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->args->death);
		if (monitoring_philos_state(philo))
		{
			sem_wait(philo->args->lock_print_log);
			sem_post(philo->args->process);
			break ;
		}
		sem_post(philo->args->death);
		sem_wait(philo->args->death);
		if (philo->args->max_meals_mode && monitoring_meal_count(philo))
		{
			sem_post(philo->args->process);
			break ;
		}
		sem_post(philo->args->death);
	}
	return (NULL);
}
