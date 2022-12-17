/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/18 00:42:07 by ilandols         ###   ########.fr       */
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
	long long		last_meal;
	struct s_arg	*args;
}	t_philo;

typedef struct s_arg {
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				meal_counter;
	t_bool			count_max_meals;
	t_bool			philo_is_alive;
	t_bool			end_meal;
	struct timeval	meal_time;
	pthread_mutex_t *forks;
	pthread_mutex_t	print_log;
	pthread_mutex_t	check_philo_life;
	pthread_mutex_t	check_philo_life2;
	pthread_mutex_t	check_last_meal;
	pthread_t		meal_thread;
	t_philo			*philos;
}	t_arg;

/* philo_utils.c */
long long	convert_timeval(struct timeval base);
long long	get_timestamp(struct timeval meal_time);
void		print_log(t_arg *args, int philo_id, char *log);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

/* run.c */
void		*check_end(void *strouct);
void		run(t_arg *args, t_philo *philos);

/* interaction_philo.c */
void		think_deeply(t_philo *philo);
void		go_to_bed(t_philo *philo);
void		think_deeply(t_philo *philo);
void		eat(t_philo *philo);
void		*meal_time(void *arg);

/* initialize.c */
void		initialize_structs(t_arg *args, t_philo **philos, char **parameters);

/* utils.c */
long long	ft_long_long_atoi(const char *nptr);
int			ft_isdigit(int c);
int			ft_str_isdigit(char *str);

/* parsing.c */
int 		is_valid_parameters(int nb_parameters, char **parameters);

/* main.c */
int			main(int ac, char **av);

#endif