/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:08 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/17 18:05:05 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	convert_timeval(struct timeval base)
{
	long long	result;

	result = (base.tv_sec * 1000) + (base.tv_usec / 1000);
	return (result);
}

// void	usloup(t_philo *philo, long long useconds)
// {
// 	struct timeval	t_current;
// 	struct timeval	t_target;
// 	long long		current;
// 	long long		target;

// 	gettimeofday(&t_current, NULL);
// 	gettimeofday(&t_target, NULL);
// 	current = convert_timeval(t_current);
// 	target = convert_timeval(t_current) + useconds / 1000;
// 	while (current < target)
// 	{
// 		if (!check_philo_state(philo))
// 		{
// 			print_log(philo->args, philo->id, LOG_DIE);
// 			philo->args->philo_is_alive = FALSE;
// 			break ;
// 		}
// 		// printf("[%ld] [%ld]\n", current, target);
// 		gettimeofday(&t_current, NULL);
// 		current = convert_timeval(t_current);
// 	}
// }

void	usloup(t_philo *philo, long long useconds)
{
	struct timeval	t_current;
	long long		current;
	long long		target;

	gettimeofday(&t_current, NULL);
	current = convert_timeval(t_current) * 1000;
	target = convert_timeval(t_current) * 1000 + useconds;
	while (current < target)
	{
		if (!check_philo_state(philo))
		{
			print_log(philo->args, philo->id, LOG_DIE);
			philo->args->philo_is_alive = FALSE;
			break ;
		}
		gettimeofday(&t_current, NULL);
		current = convert_timeval(t_current) * 1000;
	}
}

int		check_philo_state(t_philo *philo)
{
	if (get_timestamp(philo->args->meal_time) - philo->last_meal > philo->args->time_to_die)
		return (0);
	return (1);
}

long long	get_timestamp(struct timeval meal_time)
{
	struct timeval	philo;

	gettimeofday(&philo, NULL);
	return (convert_timeval(philo) - convert_timeval(meal_time));
}

void	print_log(t_arg *args, int philo_id, char *log)
{
	pthread_mutex_lock(&args->meal);
	if (args->philo_is_alive)
	{
		pthread_mutex_lock(&args->print);
		printf("[%lldms] Philo %d %s\n", get_timestamp(args->meal_time), philo_id, log);
		pthread_mutex_unlock(&args->print);
	}
	pthread_mutex_unlock(&args->meal);
}

void	take_fork(t_philo *philo)
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
