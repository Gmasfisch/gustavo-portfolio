/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:20:17 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/23 18:01:23 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philosopher **philo, t_data *data)
{
	int		i;

	i = 0;
	data->finished = 0;
	*philo = malloc(sizeof(t_philosopher) * data->philo_num);
	pthread_mutex_init(&data->count_mutex, NULL);
	if (!(*philo))
		return (-1);
	while (i < data->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].data = data;
		i++;
	}
	data->philos = *philo;
	return (0);
}

t_data	*init_data(char **argv)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->stop = 0;
	if (argv[5])
		data->count_to_eat = ft_atoi(argv[5]);
	else
		data->count_to_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (free(data), NULL);
	i = 0;
	while (i < data->philo_num)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	return (data);
}
