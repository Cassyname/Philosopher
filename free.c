/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:02 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/01 15:07:59 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

void	ft_free(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philo)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	if (data->thread)
		free(data->thread);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	if (data->print)
		pthread_mutex_destroy(data->print);
	if (str)
		printf("%s", str);
}
