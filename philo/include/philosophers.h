/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/11 16:46:15 by ilandols         ###   ########.fr       */
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

typedef struct s_philo {
	t_bool			is_eating;
	t_bool			is_thinking;
	t_bool			is_sleeping;
	struct s_philo	*next;
} t_philo;

/* parsing.c */
int 		is_valid_parameters(int ac, char **av);

/* utils.c */
long long	ft_long_long_atoi(const char *nptr);
int			ft_isdigit(int c);
int			ft_str_isdigit(char *str);

/* main.c */
int			main(int ac, char **av);

#endif