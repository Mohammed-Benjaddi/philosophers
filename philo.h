/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:41 by mben-jad          #+#    #+#             */
/*   Updated: 2024/08/18 15:59:17 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define GREEN "\x1b[32m"
# define CYAN "\x1b[36m"
# define RED "\x1b[31m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define WHITE "\x1b[37m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	int					last_meal;
	pthread_mutex_t		is_eating;
	pthread_mutex_t		check_meal;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					n_philos;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		dead_mutex;
	int					is_dead;
	int					finished;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long long			start_time;
	int					times_to_eat;
	int					all_philos_ate;
	pthread_mutex_t		all_ate_mutex;
}						t_data;

void					ft_error(char *str);
int						ft_atoi(char *str);
int						init_program(char **args, t_data *data);
void					*philo_routine(void *data);
int						get_current_time(void);
void					ft_wait(int ms);
void					destroy_all_forks(t_data *data, int size);
void					ft_think(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_eat(t_philo *phi);
void					*philo_routine(void *data);
void					print_msg(t_philo *philo, char *color,
							char *description);
void					check_dead_philo(t_data *data);
void					start_program(t_data *data);
int						is_valid_nbr(char *nbr);
int						parsing(char **args);
void					ft_free(void **arr);

#endif
