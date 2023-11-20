/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:11 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/11/01 16:16:48 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_thread(t_data *data)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread)
		ft_free(data, "Error\nmalloc\n");
	data->thread = thread;
}

void	init_print_mutex(t_data *data, pthread_mutex_t *print)
{
	pthread_mutex_init(print, NULL);
	data->print = print;
}

void	init_all(t_data *data, char **argv)
{
	init_data_info(data);
	init_param(data, argv);
	init_philo(data);
}

int	main(int argc, char **argv)
{
	int				i;
	t_data			data;
	pthread_t		dead;
	pthread_mutex_t	print;

	i = 1;
	while (i <= argc)
		check_philo(argc, argv[i++]);
	i = -1;
	init_all(&data, argv);
	init_print_mutex(&data, &print);
	pthread_create(&dead, NULL, &check_death, (void *)&data);
	while (++i < data.nb_philo)
	{
		pthread_create(&data.thread[i], NULL, &philo_life, \
				(void *)&data.philo[i]);
		ft_usleep(&data.philo[i], !(i % 2));
	}
	i = 0;
	while (i < data.nb_philo)
		pthread_join(data.thread[i++], NULL);
	pthread_join(dead, NULL);
	ft_free(&data, 0);
	return (0);
}
