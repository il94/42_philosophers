/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:01:31 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/20 20:16:44 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/philosophers.h"

// int	main(int ac, char **av)
// {
// 	t_arg	args;
// 	t_philo	*philos;

// 	if (!is_valid_parameters(ac - 1, av + 1))
// 		exit (EXIT_FAILURE);
// 	initialize_struct(&args, &philos, av + 1);
// 	run(&args, philos);
// 	free(args.forks);
// 	free(philos);
// 	return (0);
// }

# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_test {
	char str1[5];
	char str2[5];
	pthread_t	thread;
	sem_t		semaphore;
}	t_test;

void	*B(void *arg)
{
	t_test	*var;

	var = (t_test *)arg;
	sem_wait(&var->semaphore);
	printf("str = %s\n", var->str2);
	var->str2[2] = 'B';
	printf("str = %s\n", var->str2);
	sem_post(&var->semaphore);
	return (NULL);
}

void	*A(void *arg)
{
	t_test	*var;

	var = (t_test *)arg;
	sem_wait(&var->semaphore);
	printf("str = %s\n", var->str1);
	var->str1[2] = 'A';
	printf("str = %s\n", var->str1);
	sem_post(&var->semaphore);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_test		var;

	var.str1[0] = 'p';
	var.str1[1] = 'l';
	var.str1[2] = 'o';
	var.str1[3] = 'p';
	var.str1[4] = '\0';
	var.str2[0] = 'p';
	var.str2[1] = 'l';
	var.str2[2] = 'o';
	var.str2[3] = 'p';
	var.str2[4] = '\0';
	sem_init(&var.semaphore, 0, 1);
	pthread_create(&var.thread, NULL, A, &var);
	pthread_create(&var.thread, NULL, B, &var);
	pthread_join(var.thread, NULL);
	pthread_join(var.thread, NULL);
	// sem_post(&semaphore);
	sem_wait(&var.semaphore);
	sem_destroy(&var.semaphore);
	return (0);
}
