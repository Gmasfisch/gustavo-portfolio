/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:52:51 by gfischba          #+#    #+#             */
/*   Updated: 2025/11/24 13:50:13 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <signal.h>

# define RESET "\033[0m"
# define MAGENTA "\033[35m"
# define BLUE "\033[34m"
# define RED "\033[31m"

typedef struct s_semaphores
{
	sem_t		*forks;
	sem_t		*print;
	sem_t		*meals_done;
	sem_t		*last_meal_sem;
	sem_t		*room_sem;
	const char	*forks_name;
	const char	*print_name;
	const char	*meals_done_name;
	const char	*last_meal_sem_name;
	const char	*room_sem_name;
}	t_semaphores;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				philo_id;
	int				death_stop;
	long long		last_meal;
	long long		start_time;
	pid_t			*philo_pid;
	t_semaphores	*sems;
	pthread_t		monitor_death;
}	t_data;

int				ft_atoi(const char *nptr);
t_data			*init_data(char **argv);
int				check_sem_failure(t_semaphores *sems);
t_semaphores	*init_sems(t_data *data);
void			wait_all(t_data *data);
int				check_meals(t_data *data, pid_t *philo_pid);
int				fork_philos(t_data *data);
void			pick_forks(t_data *data);
void			eat(t_data *data);
long long		elapsed_time(t_data *data);
long long		get_time_in_ms(void);
void			philo_sleep(t_data *data);
void			think(t_data *data);
void			philosopher_routine(t_data *data);
void			kill_all(t_data *data);
void			*monitor_death(void *arg);
void			close_and_unlink(t_semaphores *sems);
void			clean_all(t_data *data, t_semaphores *sems);
void			print_action(t_data *data, int id, char *msg);
void			*monitor_meals(void *arg);
void			fork_loop(t_data *data);
int				check_args(char **argv);
int				init_lastmeal_sem(t_semaphores *sems);
long long		check_last_meal(t_data *data);
void			close_sems(t_semaphores *sems);
void			set_routine_death(t_data *data);

#endif