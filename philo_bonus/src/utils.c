/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:33:00 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/02 15:26:30 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	convert_timeval(struct timeval base)
{
	long long	result;

	result = (base.tv_sec * 1000) + (base.tv_usec / 1000);
	return (result);
}

long long	get_timestamp(struct timeval start)
{
	struct timeval	curent;

	gettimeofday(&curent, NULL);
	return (convert_timeval(curent) - convert_timeval(start));
}

long long	ft_long_long_atoi(const char *nptr)
{
	int			i;
	int			symb;
	long long	result;

	i = 0;
	symb = 1;
	result = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		symb *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * symb);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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
