/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:51:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/28 10:13:16 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher_routine(t_data *data)
{
	int	meals_eaten;

	meals_eaten = 0;
	sem_wait(data->sems->last_meal_sem);
	data->last_meal = get_time_in_ms();
	sem_post(data->sems->last_meal_sem);
	if (pthread_create(&data->monitor_death, NULL, monitor_death, data) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(data->monitor_death);
	while (!data->death_stop)
	{
		pick_forks(data);
		eat(data);
		meals_eaten++;
		philo_sleep(data);
		if (data->eat_count != -1 && meals_eaten >= data->eat_count)
			break ;
		think(data);
	}
	set_routine_death(data);
	exit(EXIT_SUCCESS);
}

void	think(t_data *data)
{
	print_action(data, data->philo_id, "is thinking");
	usleep(200);
}

void	philo_sleep(t_data *data)
{
	long long	time;

	time = get_time_in_ms();
	print_action(data, data->philo_id, "is sleeping");
	while (get_time_in_ms() - time < data->time_to_sleep)
		usleep(200);
}

void	pick_forks(t_data *data)
{
	sem_wait(data->sems->room_sem);
	sem_wait(data->sems->forks);
	print_action(data, data->philo_id, "has taken a fork");
	sem_wait(data->sems->forks);
	print_action(data, data->philo_id, "has taken a fork");
	sem_post(data->sems->room_sem);
}

void	eat(t_data *data)
{
	long long	start;

	start = get_time_in_ms();
	sem_wait(data->sems->last_meal_sem);
	data->last_meal = get_time_in_ms();
	sem_post(data->sems->last_meal_sem);
	print_action(data, data->philo_id, "is eating");
	while (get_time_in_ms() - start < data->time_to_eat)
		usleep(200);
	sem_post(data->sems->forks);
	sem_post(data->sems->forks);
}
