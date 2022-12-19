/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_data_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:47:52 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/19 21:23:57 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	secure_check_end_meal(t_arg *args)
{
	pthread_mutex_lock(&args->check_end_meal);
	if (args->end_meal)
	{
		pthread_mutex_unlock(&args->check_end_meal);
		return (1);
	}
	pthread_mutex_unlock(&args->check_end_meal);
	return (0);
}

void	secure_set_end_meal(t_arg *args)
{
	pthread_mutex_lock(&args->check_end_meal);
	args->end_meal = TRUE;
	pthread_mutex_unlock(&args->check_end_meal);
}

void	secure_set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check_last_meal);
	philo->last_meal = get_timestamp(philo->args->start_meal);
	pthread_mutex_unlock(&philo->args->check_last_meal);
}

void	secure_set_has_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check_has_eaten);
	philo->has_eaten = TRUE;
	pthread_mutex_unlock(&philo->args->check_has_eaten);
}
