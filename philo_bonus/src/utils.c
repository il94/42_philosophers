/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:33:00 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/04 14:40:34 by ilandols         ###   ########.fr       */
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
