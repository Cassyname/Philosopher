/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:03:09 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/01 16:30:11 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - 48);
	return (result * sign);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	start_time(t_data *data)
{
	return (timestamp() - data->start_time);
}

void	ft_usleep(t_info *info, long long time)
{
	long long	start;

	start = timestamp();
	while (timestamp() < start + time)
	{
		pthread_mutex_lock(&info->data->dead);
		if (info->philo_dead)
		{
			pthread_mutex_unlock(&info->data->dead);
			break ;
		}
		pthread_mutex_unlock(&info->data->dead);
		usleep(500);
	}
}

void	print(t_data *data, t_info *info, char *str)
{
	if (info->philo_dead)
		return ;
	pthread_mutex_lock(data->print);
	if (!(info->philo_dead))
		printf("%lld %d %s", start_time(data), info->id + 1, str);
	pthread_mutex_unlock(data->print);
}
