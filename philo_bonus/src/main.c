/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/24 00:22:10 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;

	if (!is_valid_parameters(ac - 1, av + 1))
		exit (EXIT_FAILURE);
	initialize_struct(&args, &philos, av + 1);
	run(&args, philos);
	free_memory(&args, FALSE);
	return (0);
}
