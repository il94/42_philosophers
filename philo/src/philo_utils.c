/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:08 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/18 00:44:07 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	convert_timeval(struct timeval base)
{
	long long	result;

	result = (base.tv_sec * 1000) + (base.tv_usec / 1000);
	return (result);
}

long long	get_timestamp(struct timeval meal_time)
{
	struct timeval	philo;

	gettimeofday(&philo, NULL);
	return (convert_timeval(philo) - convert_timeval(meal_time));
}

void	print_log(t_arg *args, int philo_id, char *log)
{
	pthread_mutex_lock(&args->check_philo_life2);
	if (!args->end_meal)
	{
		pthread_mutex_lock(&args->print_log);
		printf("[%lldms] Philo %d %s\n", get_timestamp(args->meal_time), philo_id, log);
		pthread_mutex_unlock(&args->print_log);
	}
	pthread_mutex_unlock(&args->check_philo_life2);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo->args, philo->id, LOG_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_log(philo->args, philo->id, LOG_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo->args, philo->id, LOG_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_log(philo->args, philo->id, LOG_FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
