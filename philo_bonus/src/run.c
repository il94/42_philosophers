/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:49:01 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/24 00:19:52 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	start_process(t_arg *args, t_philo *philos)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 1;
	while (i < args->number_of_philosophers)
	{
		if (pid != 0)
		{
			pid = fork();
			if (pid == 0)
				meal_time(&philos[i]);
		}
		if (pid < 0)
			free_memory(args, TRUE);
		philos[i].pid = pid;
		i++;
	}
}	

static void	end_process(t_arg *args, t_philo *philos)
{
	int		i;

	waitpid(-1, NULL, 0);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
}	

// static void	create_all_forks(t_arg *args, t_philo *philos)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		return_process_value;

// 	i = 0;
// 	pid = 1;
// 	while (i < args->number_of_philosophers)
// 	{
// 		if (pid != 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 				meal_time(&philos[i]);
// 		}
// 		if (pid < 0)
// 			free_all_and_exit(args);
// 		philos[i].pid = pid;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < args->number_of_philosophers)
// 	{
// 		waitpid(-1, &return_process_value, 0);
// 		if (return_process_value != 0)
// 		{
// 			i = 0;
// 			while (i < args->number_of_philosophers)
// 			{
// 				kill(philos[i].pid, SIGKILL);
// 				i++;
// 			}
// 			break ;
// 		}
// 		i++;
// 	}
// }

void	run(t_arg *args, t_philo *philos)
{
	start_process(args, philos);
	end_process(args, philos);
}
