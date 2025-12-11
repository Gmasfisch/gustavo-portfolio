/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:49:43 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/23 20:27:00 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	data->eat_count = -1;
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
	data->start_time = 0;
	data->last_meal = 0;
	data->philo_pid = malloc(sizeof(pid_t) * data->philo_num);
	if (!data->philo_pid)
	{
		free(data);
		return (NULL);
	}
	i = -1;
	while (++i < data->philo_num)
		data->philo_pid[i] = -1;
	return (data);
}

t_semaphores	*init_sems(t_data *data)
{
	t_semaphores	*sems;

	data->death_stop = 0;
	sems = malloc(sizeof(t_semaphores));
	if (!sems)
		return (NULL);
	sems->forks_name = "/fork_sem";
	sems->print_name = "/print_sem";
	sems->meals_done_name = "/meals_done";
	sem_unlink(sems->forks_name);
	sem_unlink(sems->print_name);
	sem_unlink(sems->meals_done_name);
	sems->forks = sem_open(sems->forks_name, O_CREAT
			| O_EXCL, 0644, data->philo_num);
	sems->print = sem_open(sems->print_name, O_CREAT | O_EXCL, 0644, 1);
	sems->meals_done = sem_open(sems->meals_done_name, O_CREAT
			| O_EXCL, 0644, 0);
	init_lastmeal_sem(sems);
	return (sems);
}

int	init_lastmeal_sem(t_semaphores *sems)
{
	sems->last_meal_sem_name = "/last_meal_sem";
	sems->room_sem_name = "/room_sem";
	sem_unlink(sems->last_meal_sem_name);
	sem_unlink(sems->room_sem_name);
	sems->last_meal_sem = sem_open(sems->last_meal_sem_name,
			O_CREAT | O_EXCL, 0644, 1);
	sems->room_sem = sem_open(sems->room_sem_name,
			O_CREAT | O_EXCL, 0644, 1);
	if (!check_sem_failure(sems))
		return (0);
	return (1);
}
