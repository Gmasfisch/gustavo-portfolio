/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:41:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/23 20:17:02 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	t_semaphores	*sems;

	if (argc < 5 || argc > 6)
		return (-1);
	if (!check_args(argv))
		return (-1);
	data = init_data(argv);
	if (!data)
		return (-1);
	sems = init_sems(data);
	if (!sems)
	{
		clean_all(data, sems);
		return (-1);
	}
	data->sems = sems;
	if (fork_philos(data) == -1)
	{
		clean_all(data, sems);
		return (-1);
	}
	return (0);
}

long long	check_last_meal(t_data *data)
{
	long long	check;

	sem_wait(data->sems->last_meal_sem);
	check = data->last_meal;
	sem_post(data->sems->last_meal_sem);
	return (check);
}
