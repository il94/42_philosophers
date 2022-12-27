/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_data_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:47:52 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/27 16:53:31 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
