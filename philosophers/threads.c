/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:20:28 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/19 18:13:52 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philos_threads(t_philosopher *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			write(2, "thread join failed\n", 20);
			set_stop(data);
		}
		i++;
	}
}

void	create_philos_threads(t_philosopher *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->philo_num)
	{
		philo[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philosopher_routine, &philo[i]) != 0)
		{
			write(2, "thread join failed\n", 20);
			set_stop(data);
			break ;
		}
		i++;
	}
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (!check_stop(data))
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (!monitor_loop(data, i))
				return (NULL);
			i++;
		}
		if (data->count_to_eat > 0 && check_finished(data) == data->philo_num)
		{
			set_stop(data);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	monitor_loop(t_data *data, int i)
{
	if (check_death(data, i))
		return (0);
	return (1);
}
