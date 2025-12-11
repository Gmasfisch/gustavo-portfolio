/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:19:23 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:23 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philo;
	t_data			*data;
	pthread_t		monitor_thread;

	if (argc < 5 || argc > 6)
		return (1);
	if (!check_args(argv))
		return (1);
	data = init_data(argv);
	init_philo(&philo, data);
	create_philos_threads(philo, data);
	if (pthread_create(&monitor_thread, NULL, monitor_death, data) != 0)
	{
		write(2, "monitor thread creation failed\n", 32);
		return (1);
	}
	join_philos_threads(philo, data);
	pthread_join(monitor_thread, NULL);
	free_all(philo, data);
	return (0);
}
