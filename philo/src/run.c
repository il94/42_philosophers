/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/17 16:58:13 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	run(t_arg args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, graillance, &philos[i]))
			exit (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL))
			exit (EXIT_FAILURE);
		i++;
	}
}
