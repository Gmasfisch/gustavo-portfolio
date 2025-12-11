/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_monitors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:41:32 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/28 10:11:10 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	fork_philos(t_data *data)
{
	pthread_t	monitor;

	data->start_time = get_time_in_ms();
	if (data->eat_count != -1)
	{
		if (pthread_create(&monitor, NULL, monitor_meals, data) != 0)
		{
			close_and_unlink(data->sems);
			clean_all(data, data->sems);
			return (-1);
		}
		pthread_detach(monitor);
	}
	fork_loop(data);
	wait_all(data);
	close_and_unlink(data->sems);
	clean_all(data, data->sems);
	return (0);
}

void	fork_loop(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->philo_num)
	{
		pid = fork();
		data->philo_pid[i] = pid;
		if (pid < 0)
			write(2, "fork failed\n", 13);
		if (pid == 0)
		{
			data->philo_id = i + 1;
			philosopher_routine(data);
		}
		i++;
	}
}

void	*monitor_death(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	while (!data->death_stop)
	{
		if (get_time_in_ms() - check_last_meal(data) >= data->time_to_die)
		{
			sem_wait(data->sems->print);
			printf("%lld %d has died\n", elapsed_time(data), data->philo_id);
			close_sems(data->sems);
			clean_all(data, data->sems);
			exit(EXIT_FAILURE);
		}
		usleep(100);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		eaten_philos;

	data = (t_data *) arg;
	eaten_philos = 0;
	while (eaten_philos < data->philo_num)
	{
		sem_wait(data->sems->meals_done);
		eaten_philos++;
	}
	kill_all(data);
	return (NULL);
}

int	check_sem_failure(t_semaphores *sems)
{
	if (sems->forks == SEM_FAILED || sems->print == SEM_FAILED
		|| sems->meals_done == SEM_FAILED
		|| sems->last_meal_sem == SEM_FAILED
		|| sems->room_sem == SEM_FAILED)
	{
		close_and_unlink(sems);
		free(sems);
		return (0);
	}
	return (1);
}
