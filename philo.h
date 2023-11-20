/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:25:07 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/02 11:12:49 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				id;
	int				philo_dead;
	int				nb_eat;
	long long		last_eat;
	struct s_data	*data;
}			t_info;

typedef struct s_data
{
	int				nb_philo;
	int				nb_forks;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	long long		start_time;
	t_info			*philo;
	pthread_t		*thread;
	pthread_mutex_t	dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
}		t_data;

/* main.c  */
void		init_thread(t_data *data);
void		init_print_mutex(t_data *data, pthread_mutex_t *print);
void		init_all(t_data *data, char **argv);
/* init.c */
void		init_data_info(t_data *data);
void		init_param(t_data *data, char **argv);
void		init_nb_philo(t_data *data, t_info *info, int i);
void		init_philo(t_data *data);
void		init_mutex_fork(t_data *data);
/* check.c  */
void		check_philo(int argc, char *str);
int			all_philo_eat(t_data *data);
int			philo_dead(t_data *data, int i);
/* thread.c */
void		*check_death(void *arg);
void		*philo_life(void *arg);
int			routine(t_data *data, t_info *info, int left_fork, int right_fork);
void		unlock_mutex(t_data *data, int left_fork, int right_fork);
int			philo_are_dead(t_info *info, int i, int left_fork, int right_fork);
/* utils.c  */
int			ft_atoi(char *str);
long long	timestamp(void);
long long	start_time(t_data *data);
void		ft_usleep(t_info *info, long long time);
void		print(t_data *data, t_info *info, char *str);
/* free.c  */
void		ft_exit(char *str);
void		ft_free(t_data *data, char *str);
#endif
