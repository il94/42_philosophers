/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:11:22 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/27 17:02:51 by ilandols         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <wait.h>
# include <limits.h>

# define LOG_FORK "has taken a fork"
# define LOG_EAT "is eating"
# define LOG_SLEEP "is sleeping"
# define LOG_THINK "is thinking"
# define LOG_DIE "died"

typedef enum e_exit {
	CONTINUE,
	EXIT
}	t_exit;

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo {
	int				id;
	pid_t			pid;
	t_bool			has_eaten;
	long long		last_meal;
	struct s_arg	*args;
}	t_philo;

typedef struct s_arg {
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_think;
	int				max_meals;
	int				meal_counter;
	t_bool			max_meals_mode;
	struct timeval	start_meal;
	sem_t			*process;
	sem_t			*death;
	sem_t			*forks;
	sem_t			*lock_print_log;
	sem_t			*check_last_meal;
	sem_t			*check_has_eaten;
	t_philo			*philos;
}	t_arg;

/* secure_data_access.c */
void		secure_set_last_meal(t_philo *philo);
void		secure_set_has_eaten(t_philo *philo);

/* meal_monitoring.c */
void		*meal_monitoring(void *arg);

/* meal_time_utils.c */
void		secure_print_log_end(t_arg *args, int philo_id, char *log);
void		secure_print_log(t_arg *args, int philo_id, char *log);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

/* meal_time.c */
void		meal_time(t_philo *philo);

/* run.c */
void		run(t_arg *args);

/* initialize.c */
void		initialize_struct(t_arg *args, char **parameters);

/* parsing.c */
int			is_valid_parameters(int nb_parameters, char **parameters);

/* utils.c */
long long	convert_timeval(struct timeval base);
long long	get_timestamp(struct timeval start);
long long	ft_long_long_atoi(const char *nptr);
int			ft_str_isdigit(char *str);
void		free_memory(t_arg *args, t_exit exit_bool);

/* main.c */
int			main(int ac, char **av);

#endif