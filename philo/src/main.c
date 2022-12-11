/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/11 19:13:30 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	hello(void)
{
	printf("hello\n");
	return (0);
}

int main(int ac, char **av)
{
	t_philo	*philos;
	pthread_t	*thread;
	
	if (!is_valid_parameters(ac - 1, av + 1))
		exit (1);
	pthread_create(thread, NULL, hello(), NULL);
	return (0);
}
