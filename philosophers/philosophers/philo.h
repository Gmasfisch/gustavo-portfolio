/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:03:37 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/19 18:14:05 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_philosopher;

typedef struct s_data
{
	int						philo_num;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						count_to_eat;
	int						stop;
	int						finished;
	long long				start_time;
	pthread_mutex_t			stop_mutex;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			meal_mutex;
	pthread_mutex_t			count_mutex;
	struct s_philosopher	*philos;
}	t_data;

typedef struct s_philosopher
{
	int				id;
	int				eat_count;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philosopher;

int			ft_atoi(const char *nptr);
t_data		*init_data(char **argv);
int			init_philo(t_philosopher **philo, t_data *data);
void		*philosopher_routine(void *arg);
void		eat(t_philosopher *philo);
void		create_philos_threads(t_philosopher *philo, t_data *data);
void		think(t_philosopher *philo);
void		philo_sleep(t_philosopher *philo);
void		put_forks(t_philosopher *philo);
int			pick_right_first(t_philosopher *philo,
				int right_fork, int left_fork);
int			pick_left_first(t_philosopher *philo,
				int left_fork, int right_fork);
int			pick_forks(t_philosopher *philo);
void		join_philos_threads(t_philosopher *philo, t_data *data);
void		*monitor_death(void *arg);
int			check_death(t_data *data, int i);
void		free_all(t_philosopher *philo, t_data *data);
long long	elapsed_time(t_data *data);
long long	get_time_in_ms(void);
void		print_action(t_data *data, int id, char *msg);
int			monitor_loop(t_data *data, int i);
void		set_stop(t_data *data);
void		just_one_philo(t_philosopher *philo, int left_fork);
int			check_stop(t_data *data);
int			check_args(char **argv);
int			check_finished(t_data *data);

#endif