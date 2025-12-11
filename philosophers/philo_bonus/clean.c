/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:51:01 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/25 15:11:53 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_all(t_data *data, t_semaphores *sems)
{
	if (data)
	{
		if (data->philo_pid)
			free(data->philo_pid);
		free(data);
	}
	if (sems)
		free(sems);
}

void	close_and_unlink(t_semaphores *sems)
{
	if (sems->forks != SEM_FAILED)
	{
		sem_close(sems->forks);
		sem_unlink(sems->forks_name);
	}
	if (sems->meals_done != SEM_FAILED)
	{
		sem_close(sems->meals_done);
		sem_unlink(sems->meals_done_name);
	}
	if (sems->print != SEM_FAILED)
	{
		sem_close(sems->print);
		sem_unlink(sems->print_name);
	}
	if (sems->last_meal_sem != SEM_FAILED)
	{
		sem_close(sems->last_meal_sem);
		sem_unlink(sems->last_meal_sem_name);
	}
	if (sems->room_sem != SEM_FAILED)
	{
		sem_close(sems->room_sem);
		sem_unlink(sems->room_sem_name);
	}
}

void	close_sems(t_semaphores *sems)
{
	sem_close(sems->forks);
	sem_close(sems->last_meal_sem);
	sem_close(sems->meals_done);
	sem_close(sems->print);
	sem_close(sems->room_sem);
}

void	set_routine_death(t_data *data)
{
	if (data->eat_count != -1)
	{
		sem_post(data->sems->meals_done);
		data->death_stop = 1;
	}
	usleep(200);
	close_and_unlink(data->sems);
	clean_all(data, data->sems);
}
