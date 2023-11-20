/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:53:24 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/02 11:12:16 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_info(t_data *data)
{
	data->nb_philo = -1;
	data->nb_forks = 0;
	data->time_die = -1;
	data->time_eat = -1;
	data->time_sleep = -1;
	data->nb_eat = -1;
	data->start_time = timestamp();
	data->philo = NULL;
	data->thread = NULL;
}

void	init_param(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->nb_forks = data->nb_philo;
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	if (data->nb_philo <= 0)
		ft_exit("Error\nArgv[1] must not be null\n");
	if (data->nb_philo == 1)
	{
		printf("0 1 has taken fork\n");
		usleep(data->time_die * 1000);
		printf("%d 1 died\n", data->time_die);
		exit(1);
	}
	if (argv[5] && data->nb_eat <= 0)
		ft_exit("Error\nArgv[5] must not be null\n");
}

void	init_nb_philo(t_data *data, t_info *info, int i)
{
	info->id = i;
	info->philo_dead = 0;
	info->nb_eat = 0;
	info->last_eat = 0;
	info->data = data;
}

void	init_philo(t_data *data)
{
	t_info	*info;
	int		i;

	info = malloc(sizeof(t_info) * data->nb_philo);
	i = 0;
	if (!info)
		ft_free(data, "Error\nmalloc\n");
	while (i < data->nb_philo)
	{
		init_nb_philo(data, &info[i], i);
		i++;
	}
	data->philo = info;
	init_mutex_fork(data);
	init_thread(data);
}

void	init_mutex_fork(t_data *data)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	i = 0;
	if (!forks)
		ft_free(data, "Error\nmalloc\n");
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->dead, NULL);
	data->forks = forks;
}
