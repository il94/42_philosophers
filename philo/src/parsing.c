/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:03:21 by ilandols          #+#    #+#             */
/*   Updated: 2023/01/02 16:21:25 by ilandols         ###   ########.fr       */
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

static int	is_valid_content_parameters(int nb_parameters, char **parameters)
{
	int	i;

	i = 0;
	while (i < nb_parameters)
	{
		if (!ft_str_isdigit(parameters[i])
			|| ft_long_long_atoi(parameters[0]) <= 0
			|| !is_int(ft_long_long_atoi(parameters[i]), parameters[i]))
		{
			printf("Invalid parameters\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_valid_number_parameters(int nb_parameters)
{
	if (nb_parameters < 4 || nb_parameters > 5)
	{
		printf("Invalid number of parameters\n");
		return (0);
	}
	return (1);
}

int	is_valid_parameters(int nb_parameters, char **parameters)
{
	if (!is_valid_number_parameters(nb_parameters)
		|| !is_valid_content_parameters(nb_parameters, parameters))
		return (0);
	return (1);
}
