/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:54:32 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/15 21:20:27 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	sloup(t_philo *philo)
{
	// printf("id = %d DORMIR\n", philo->id);
	usleep(philo->args->time_to_sleep);	
	// printf("id = %d dodo fini\n", philo->id);
}

void	eat(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	take_fork(philo);
	printf("")
	if ((time.tv_usec) - (philo->args->time.tv_usec) >  philo->args->time_to_die)
	{
		philo->args->philo_is_alive = FALSE;
		return ;
	}
	else
		philo->args->time.tv_usec = time.tv_usec;
	printf("id = %d A des fourchettes\n", philo->id);
	usleep(philo->args->time_to_eat);
	// printf("id = %d manger fini\n", philo->id);
	drop_fork(philo);
}

void	*graillance(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	int	meal_number;

	meal_number = 0;
	while (philo->args->philo_is_alive)
	{
		eat(philo);
		sloup(philo);
		meal_number++;
	}
	printf("END\n");
	return (NULL);
}