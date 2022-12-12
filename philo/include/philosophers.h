/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/12 15:42:42 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_args {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_arg;

typedef struct s_philo {
	int				data;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_bool			is_eating;
	t_bool			is_thinking;
	t_bool			is_sleeping;
}	t_philo;


/* initialize.c */
void		initialize_structs(t_arg *args, t_philo **philos, char **parameters);

/* parsing.c */
int 		is_valid_parameters(int nb_parameters, char **parameters);

/* utils.c */

long long	ft_long_long_atoi(const char *nptr);
int			ft_isdigit(int c);
int			ft_str_isdigit(char *str);

/* main.c */
int			main(int ac, char **av);

#endif