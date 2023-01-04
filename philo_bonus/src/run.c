/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/04 15:03:17 by ilandols         ###   ########.fr       */
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

void	free_memory(t_arg *args, t_exit exit_bool)
{
	if (args->process != SEM_FAILED)
		sem_close(args->process);
	if (args->death != SEM_FAILED)
		sem_close(args->death);
	if (args->forks != SEM_FAILED)
		sem_close(args->forks);
	if (args->lock_print_log != SEM_FAILED)
		sem_close(args->lock_print_log);
	if (args->check_last_meal != SEM_FAILED)
		sem_close(args->check_last_meal);
	if (args->check_has_eaten != SEM_FAILED)
		sem_close(args->check_has_eaten);
	if (args->philos)
		free(args->philos);
	if (exit_bool == EXIT)
		exit (EXIT_FAILURE);
}

void	run(t_arg *args)
{
	sem_wait(args->process);
	start_process(args);
	sem_wait(args->process);
	end_process(args);
	free_memory(args, CONTINUE);
}
