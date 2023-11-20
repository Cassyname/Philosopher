/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:39:10 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/01 16:24:03 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo(int argc, char *str)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_exit("Error\nNot enought args or too much args\n");
	if (!str)
		return ;
	while (str[i])
	{
		if ((str[i] >= 7 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 126))
			ft_exit("Error\nArgs is not a number or positive num\n");
		i++;
	}
}

int	all_philo_eat(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (data->nb_eat < 0)
		return (0);
	while (i < data->nb_philo)
	{
		if (data->philo[i].nb_eat >= data->nb_eat)
			count++;
		i++;
	}
	return (count == data->nb_philo);
}

int	philo_dead(t_data *data, int i)
{
	int	j;
	int	k;
	int	eat;
	int	time_die;

	k = 0;
	eat = all_philo_eat(data);
	time_die = start_time(data) - data->philo[i].last_eat;
	if (eat || time_die > data->time_die)
	{
		j = 0;
		if (eat <= 0 && k == 0)
		{
			k = 1;
			print(data, &data->philo[i], "died\n");
		}
		pthread_mutex_lock(&data->dead);
		while (j < data->nb_philo)
			data->philo[j++].philo_dead = 1;
		pthread_mutex_unlock(&data->dead);
		j = 0;
		return (-1);
	}
	return (0);
}
