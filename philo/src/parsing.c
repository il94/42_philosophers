/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:03:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/11 16:52:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	is_int(long long value, char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i > 11 && ((input[0] != '0' || input[0] == '-' || input[0] == '+')
			&& input[1] != '0'))
		return (0);
	if (value < INT_MIN || value > INT_MAX)
		return (0);
	return (1);
}

static int	is_number(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '\0')
		return (0);
	if ((input[i] == '-' || input[i] == '+') && ft_isdigit(input[i + 1]))
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_content_parameters(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (!is_number(av[i]) || !is_int(ft_long_long_atoi(av[i]), av[i]))
		{
			printf("Invalid parameters\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_valid_number_parameters(int ac)
{
	if (ac < 4 || ac > 5)
	{
		printf("Invalid number of parameters\n");
		return (0);
	}
	return (1);
}

int is_valid_parameters(int ac, char **av)
{
	if (!is_valid_number_parameters(ac) || !is_valid_content_parameters(ac, av))
		return (0);
	return (1);
}
