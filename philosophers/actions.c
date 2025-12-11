/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:19:27 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/21 19:02:48 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	if (check_stop(philo->data))
		return (0);
	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philo_num;
	if (philo->data->philo_num == 1)
	{
		just_one_philo(philo, left_fork);
		return (0);
	}
	if (philo->id % 2 == 0)
	{
		if (!pick_right_first(philo, right_fork, left_fork))
			return (0);
	}
	else
	{
		if (!pick_left_first(philo, left_fork, right_fork))
			return (0);
	}
	return (1);
}

int	pick_left_first(t_philosopher *philo, int left_fork, int right_fork)
{
	if (check_stop(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (check_stop(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (0);
	}
	print_action(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (!check_stop(philo->data))
		print_action(philo->data, philo->id, "has taken a fork");
	return (1);
}

int	pick_right_first(t_philosopher *philo, int right_fork, int left_fork)
{
	if (check_stop(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (check_stop(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		return (0);
	}
	print_action(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (!check_stop(philo->data))
		print_action(philo->data, philo->id, "has taken a fork");
	return (1);
}

void	put_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philo_num;
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	think(t_philosopher *philo)
{
	long long	start;

	start = get_time_in_ms();
	if (!check_stop(philo->data))
		print_action(philo->data, philo->id, "is thinking");
	if (!check_stop(philo->data) && get_time_in_ms() - start < 1)
		usleep(200);
}
