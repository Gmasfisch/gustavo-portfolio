/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:21:46 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/21 11:53:51 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	if (philo->id % 2 == 0)
		usleep(1000 * philo->data->time_to_eat / 2);
	while (!check_stop(philo->data))
	{
		if (!pick_forks(philo))
			continue ;
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	print_action(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print_mutex);
	if (check_stop(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", elapsed_time(data), id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

long long	elapsed_time(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}

int	check_death(t_data *data, int i)
{
	long long	last_meal;

	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if ((get_time_in_ms() - last_meal) > data->time_to_die)
	{
		print_action(data, data->philos[i].id, "has died");
		set_stop(data);
		return (1);
	}
	return (0);
}
