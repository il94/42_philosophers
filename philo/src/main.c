/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/12 16:32:46 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*increment(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;

	philo->data++;
	// printf("data = %d\n", philo->data);
}

int main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	pthread_t	thread;
	int		i = 0;
	
	if (!is_valid_parameters(ac - 1, av + 1))
		exit (EXIT_FAILURE);
	initialize_structs(&args, &philos, av + 1);
	printf("Before\n");
	while (i < 5)
	{
		if (pthread_create(&thread, NULL, increment, philos))
			exit (EXIT_FAILURE);
		if (pthread_join(thread, NULL))
			exit (EXIT_FAILURE);
		i++;
	}
	while (i > 0)
	{
		i--;
	}
	printf("After\n");
	return (0);
}
