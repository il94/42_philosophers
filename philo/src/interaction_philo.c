/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:54:32 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/17 18:04:53 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	think(t_philo *philo)
{
	print_log(philo->args, philo->id, LOG_THINK);
}

void	sloup(t_philo *philo)
{
	print_log(philo->args, philo->id, LOG_SLEEP);
	usloup(philo, philo->args->time_to_sleep * 1000);

}

void	eat(t_philo *philo)
{
	take_fork(philo);
	print_log(philo->args, philo->id, LOG_EAT);
	usloup(philo, philo->args->time_to_eat * 1000);
	drop_fork(philo);
	philo->last_meal = get_timestamp(philo->args->meal_time);
}

void	*graillance(void *arg)
{
	t_philo	*philo;
	int		meal_counter;

	philo = (t_philo *)arg;
	meal_counter = 0;
	gettimeofday(&philo->args->meal_time, NULL);
	if (philo->id % 2 != 0)
		usleep(1);
	while (philo->args->philo_is_alive
		&& meal_counter <= philo->args->number_of_times_each_philosopher_must_eat)
	{
		if (philo->args->philo_is_alive)
			eat(philo);
		if (philo->args->philo_is_alive)
			sloup(philo);
		if (philo->args->philo_is_alive)
			think(philo);
		if (philo->args->count_meals_number == TRUE)
			meal_counter++;
		// usleep(500);
	}
	return (NULL);
}