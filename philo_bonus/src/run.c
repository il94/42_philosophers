/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/02 15:26:24 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	start_process(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			meal_time(&args->philos[i]);
		else if (args->philos[i].pid < 0)
			free_memory(args, EXIT);
		i++;
	}
}	

static void	end_process(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		kill(args->philos[i].pid, SIGKILL);
		i++;
	}
}	

void	run(t_arg *args)
{
	sem_wait(args->process);
	start_process(args);
	sem_wait(args->process);
	end_process(args);
	free_memory(args, CONTINUE);
}
