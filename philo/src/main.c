/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/15 19:11:28 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	*increment(void *arg)
// {
// 	t_philo	*philos;
// 	philos = (t_philo *)arg;

// 	printf("id = %d\n", philos->id);
// 	printf("left_fork = %lld\n", philos->left_fork);
// 	printf("right_fork = %lld\n", philos->right_fork);
// 	printf("===========\n");
// }

int main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	pthread_t	thread;
	
	if (!is_valid_parameters(ac - 1, av + 1))
		exit (EXIT_FAILURE);
	initialize_structs(&args, &philos, av + 1);

	run(args, philos);
	
	// while (i < args.number_of_philosophers)
	// {
	// 	if (pthread_create(&thread, NULL, increment, &philos[i]))
	// 		exit (EXIT_FAILURE);
	// 	if (pthread_join(thread, NULL))
	// 		exit (EXIT_FAILURE);
	// 	i++;
	// }
	// while (i > 0)
	// {
	// 	i--;
	// }
	free(philos);
	return (0);
}
