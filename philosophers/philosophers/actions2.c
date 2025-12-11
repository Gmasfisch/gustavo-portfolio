/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:19:53 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/23 18:02:03 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo)
{
	long long	start;

	start = get_time_in_ms();
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (!check_stop(philo->data))
		print_action(philo->data, philo->id, "is eating");
	while (!check_stop(philo->data) && get_time_in_ms() - start
		< philo->data->time_to_eat)
		usleep(200);
	pthread_mutex_lock(&philo->data->count_mutex);
	philo->eat_count++;
	if (philo->data->count_to_eat > 0
		&& philo->eat_count == philo->data->count_to_eat)
		philo->data->finished++;
	pthread_mutex_unlock(&philo->data->count_mutex);
}

void	philo_sleep(t_philosopher *philo)
{
	long long	start;

	if (!check_stop(philo->data))
		print_action(philo->data, philo->id, "is sleeping");
	start = get_time_in_ms();
	while (!check_stop(philo->data) && get_time_in_ms()
		- start < philo->data->time_to_sleep)
		usleep(200);
}

void	free_all(t_philosopher *philo, t_data *data)
{
	int	i;

	if (data)
	{
		if (data->forks)
		{
			i = 0;
			while (i < data->philo_num)
				pthread_mutex_destroy(&data->forks[i++]);
			free(data->forks);
		}
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		pthread_mutex_destroy(&data->count_mutex);
		free(data);
	}
	if (philo)
		free(philo);
}
