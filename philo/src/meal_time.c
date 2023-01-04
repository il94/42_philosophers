/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:54:32 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/04 15:16:48 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	think_deeply(t_philo *philo)
{
	secure_print_log(philo->args, philo->id, LOG_THINK);
}

static void	go_to_bed(t_philo *philo)
{
	secure_print_log(philo->args, philo->id, LOG_SLEEP);
	usleep(philo->args->time_to_sleep * 1000);
}

static void	eat_spaghetti(t_philo *philo)
{
	take_forks(philo);
	if (philo->args->number_of_philosophers == 1)
	{
		usleep(philo->args->time_to_die * 1000 + 500);
		drop_forks(philo);
		return ;
	}
	secure_print_log(philo->args, philo->id, LOG_EAT);
	usleep(philo->args->time_to_eat * 1000);
	drop_forks(philo);
	secure_set_last_meal(philo);
	secure_set_has_eaten(philo);
}

void	*meal_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
	{
		think_deeply(philo);
		usleep(philo->args->time_to_think * 1000);
	}
	while (!secure_check_end_meal(philo->args))
	{
		eat_spaghetti(philo);
		go_to_bed(philo);
		think_deeply(philo);
		usleep(500);
	}
	return (NULL);
}
