/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:50:25 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/26 15:26:25 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
{
	int	i;

	if (!data || !data->philo_pid)
		return ;
	i = 0;
	while (i < data->philo_num)
	{
		if (data->philo_pid[i] != -1)
			kill(data->philo_pid[i], SIGKILL);
		i++;
	}
}

void	wait_all(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < data->philo_num)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all(data);
			while (waitpid(-1, NULL, 0) > 0)
				;
			return ;
		}
		i++;
	}
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	elapsed_time(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}

void	print_action(t_data *data, int id, char *msg)
{
	sem_wait(data->sems->print);
	printf("%lld %d %s\n", elapsed_time(data), id, msg);
	sem_post(data->sems->print);
}
