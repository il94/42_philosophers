/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_time_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:08 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/24 00:38:01 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	secure_print_log_end(t_arg *args, int philo_id, char *log)
{
	sem_wait(args->check_end_meal);
	if (!args->end_meal)
	{
		sem_wait(args->lock_print_log);
		printf("%lld %d %s\n", get_timestamp(args->start_meal),
			philo_id, log);
	}
	sem_post(args->check_end_meal);
}

void	secure_print_log(t_arg *args, int philo_id, char *log)
{
	sem_wait(args->check_end_meal);
	if (!args->end_meal)
	{
		sem_wait(args->lock_print_log);
		printf("%lld %d %s\n", get_timestamp(args->start_meal),
			philo_id, log);
		sem_post(args->lock_print_log);
	}
	sem_post(args->check_end_meal);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->args->forks);
	secure_print_log(philo->args, philo->id, LOG_FORK);
	if (philo->args->number_of_philosophers > 1)
	{
		sem_wait(philo->args->forks);
		secure_print_log(philo->args, philo->id, LOG_FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
}
