/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:35:41 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/02 11:12:02 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;
	int		j;

	j = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo && j == 0)
		{
			if (philo_dead(data, i) == -1)
			{
				j++;
				pthread_exit(NULL);
			}
			i++;
		}
	}
	pthread_exit(NULL);
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_data	*data;
	t_info	*info;
	int		right_fork;
	int		left_fork;

	info = (t_info *)arg;
	data = (t_data *)info->data;
	left_fork = info->id;
	right_fork = left_fork + 1;
	if (right_fork == data->nb_philo)
		right_fork = 0;
	while (1)
	{
		if (routine(data, info, left_fork, right_fork) == -1)
			break ;
	}
	return (NULL);
}

int	routine(t_data *data, t_info *info, int left_fork, int right_fork)
{
	if (philo_are_dead(info, 0, 0, 0))
		return (-1);
	pthread_mutex_lock(&data->forks[left_fork]);
	if (philo_are_dead(info, 1, left_fork, 0))
		return (-1);
	print(data, info, "has taken a fork\n");
	pthread_mutex_lock(&data->forks[right_fork]);
	if (philo_are_dead(info, 2, left_fork, right_fork))
		return (-1);
	info->last_eat = start_time(data);
	print(data, info, "has taken a fork\n");
	print(data, info, "is eating\n");
	ft_usleep(info, data->time_eat);
	info->nb_eat++;
	if (philo_are_dead(info, 2, left_fork, right_fork))
		return (-1);
	unlock_mutex(data, left_fork, right_fork);
	if (philo_are_dead(info, 0, 0, 0))
		return (-1);
	print(data, info, "is sleeping\n");
	ft_usleep(info, data->time_sleep);
	if (philo_are_dead(info, 0, 0, 0))
		return (-1);
	print(data, info, "is thinking\n");
	return (0);
}

void	unlock_mutex(t_data *data, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
}

int	philo_are_dead(t_info *info, int i, int left_fork, int right_fork)
{
	pthread_mutex_lock(&info->data->dead);
	if (info->philo_dead)
	{
		if (i >= 1)
			pthread_mutex_unlock(&info->data->forks[left_fork]);
		if (i == 2)
			pthread_mutex_unlock(&info->data->forks[right_fork]);
		pthread_mutex_unlock(&info->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&info->data->dead);
	return (0);
}
