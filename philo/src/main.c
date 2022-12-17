/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/18 00:38:07 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	
	if (!is_valid_parameters(ac - 1, av + 1))
		exit (EXIT_FAILURE);
	initialize_structs(&args, &philos, av + 1);
	run(&args, philos);
	free(args.forks);
	free(philos);
	return (0);
}
