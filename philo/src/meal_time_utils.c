/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_time_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:08 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/19 20:06:17 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	secure_print_log(t_arg *args, int philo_id, char *log)
{
	pthread_mutex_lock(&args->check_end_meal);
	if (!args->end_meal)
	{
		pthread_mutex_lock(&args->lock_print_log);
		printf("[%lldms] Philo %d %s\n", get_timestamp(args->start_meal),
			philo_id, log);
		pthread_mutex_unlock(&args->lock_print_log);
	}
	pthread_mutex_unlock(&args->check_end_meal);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		secure_print_log(philo->args, philo->id, LOG_FORK);
		pthread_mutex_lock(philo->left_fork);
		secure_print_log(philo->args, philo->id, LOG_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		secure_print_log(philo->args, philo->id, LOG_FORK);
		pthread_mutex_lock(philo->right_fork);
		secure_print_log(philo->args, philo->id, LOG_FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
