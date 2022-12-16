/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:08 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/16 19:14:39 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_timestamp(struct timeval meal_time)
{
	struct timeval	philo;

	gettimeofday(&philo, NULL);
	return ((philo.tv_sec * 1000 + philo.tv_usec / 1000) -
		(meal_time.tv_sec * 1000 + meal_time.tv_usec / 1000));
}

void	print_log(t_arg *args, int philo_id, char *log)
{
	pthread_mutex_lock(&args->print);
	printf("[%lldms] Philo %d %s\n", get_timestamp(args->meal_time), philo_id, log);
	pthread_mutex_unlock(&args->print);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

void	drop_fork(t_philo *philo)
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
