/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/20 19:06:58 by ilandols         ###   ########.fr       */
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
	t_bool			has_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_arg	*args;
}	t_philo;

typedef struct s_arg {
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				meal_counter;
	t_bool			max_meals_mode;
	t_bool			end_meal;
	struct timeval	start_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print_log;
	pthread_mutex_t	check_end_meal;
	pthread_mutex_t	check_last_meal;
	pthread_mutex_t	check_has_eaten;
	pthread_t		meal_thread;
	t_philo			*philos;
}	t_arg;

/* secure_data_access.c */
int			secure_check_end_meal(t_arg *args);
void		secure_set_end_meal(t_arg *args);
void		secure_set_last_meal(t_philo *philo);
void		secure_set_has_eaten(t_philo *philo);

/* meal_monitoring.c */
void		*meal_monitoring(void *arg);

/* meal_time_utils.c */
void		secure_print_log(t_arg *args, int philo_id, char *log);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

/* meal_time.c */
void		*meal_time(void *arg);

/* run.c */
void		run(t_arg *args, t_philo *philos);

/* initialize.c */
void		initialize_struct(t_arg *args, t_philo **philos, char **parameters);

/* parsing.c */
int			is_valid_parameters(int nb_parameters, char **parameters);

/* utils.c */
long long	convert_timeval(struct timeval base);
long long	get_timestamp(struct timeval start);
long long	ft_long_long_atoi(const char *nptr);
int			ft_str_isdigit(char *str);
void		free_all_and_exit(t_arg *args);

/* main.c */
int			main(int ac, char **av);

#endif