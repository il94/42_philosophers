/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/16 17:45:36 by ilandols         ###   ########.fr       */
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
# include <stdatomic.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# define LOG_FORK "has taken a fork"
# define LOG_EAT "is eating"
# define LOG_SLEEP "is sleeping"
# define LOG_THINK "is thinking"
# define LOG_DIE "died"

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_bool			is_eating;
	t_bool			is_thinking;
	t_bool			is_sleeping;
	long long		last_meal;
	struct s_arg	*args;
}	t_philo;

typedef struct s_arg {
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_bool			count_meals_number;
	t_philo			*philos;
	pthread_mutex_t *forks;
	pthread_mutex_t	print;
	t_bool			philo_is_alive;
	struct timeval	meal_time;
}	t_arg;

/* philo_utils.c */
long long	get_timestamp(struct timeval meal_time);
void		print_log(t_arg *args, int philo_id, char *log);
void		take_fork(t_philo *philo);
void		drop_fork(t_philo *philo);

/* run.c */
void		run(t_arg args, t_philo *philos);

/* interaction_philo.c */
void		think(t_philo *philo);
void		sloup(t_philo *philo);
void		think(t_philo *philo);
void		eat(t_philo *philo);
void		*graillance(void *arg);

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