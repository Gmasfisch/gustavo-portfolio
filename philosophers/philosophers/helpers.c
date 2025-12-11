/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:33:22 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/19 17:56:01 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	just_one_philo(t_philosopher *philo, int left_fork)
{
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	print_action(philo->data, philo->id, "has picked a fork");
	while (!philo->data->stop)
		usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	return ;
}

int	check_stop(t_data *data)
{
	int	should_stop;

	pthread_mutex_lock(&data->stop_mutex);
	should_stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (should_stop);
}

int	check_args(char **argv)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	while (argv[count])
		count++;
	i = 1;
	while (i < count)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_finished(t_data *data)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&data->count_mutex);
	check = data->finished;
	pthread_mutex_unlock(&data->count_mutex);
	return (check);
}
