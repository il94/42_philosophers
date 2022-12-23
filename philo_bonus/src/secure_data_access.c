/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_data_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:47:52 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/23 22:45:34 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	secure_check_end_meal(t_arg *args)
{
	sem_wait(args->check_end_meal);
	if (args->end_meal)
	{
		sem_post(args->check_end_meal);
		return (1);
	}
	sem_post(args->check_end_meal);
	return (0);
}

void	secure_set_end_meal(t_arg *args)
{
	sem_wait(args->check_end_meal);
	args->end_meal = TRUE;
	sem_post(args->check_end_meal);
}

void	secure_set_last_meal(t_philo *philo)
{
	sem_wait(philo->args->check_last_meal);
	philo->last_meal = get_timestamp(philo->args->start_meal);
	sem_post(philo->args->check_last_meal);
}

void	secure_set_has_eaten(t_philo *philo)
{
	sem_wait(philo->args->check_has_eaten);
	philo->has_eaten = TRUE;
	sem_post(philo->args->check_has_eaten);
}
