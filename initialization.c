/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:37 by mben-jad          #+#    #+#             */
/*   Updated: 2024/07/20 11:27:52 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error("mutex init failed"), 0);
		if (pthread_mutex_init(&data->philos[i].check_meal, NULL) != 0)
			return (ft_error("mutex init failed"), 0);
		if (pthread_mutex_init(&data->philos[i].is_eating, NULL) != 0)
			return (ft_error("mutex init failed"), 0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (ft_error("mutex init failed"), 0);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (ft_error("mutex init failed"), 0);
	if (pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
		return (ft_error("mutex init failed"), 0);
	return (1);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->n_philos;
		data->philos[i].last_meal = 0;
		i++;
	}
}

int	init_program(char **args, t_data *data)
{
	data->n_philos = ft_atoi(args[0]);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_philos);
	data->is_dead = 0;
	data->finished = 0;
	data->all_philos_ate = 0;
	data->start_time = get_current_time();
	data->time_to_die = ft_atoi(args[1]);
	data->time_to_eat = ft_atoi(args[2]);
	data->time_to_sleep = ft_atoi(args[3]);
	if (args[4])
		data->times_to_eat = ft_atoi(args[4]);
	else
		data->times_to_eat = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->n_philos <= 0
		|| data->n_philos > 200 || (args[4] && ft_atoi(args[4]) <= 0))
		return (0);
	if (!init_mutex(data))
		return (0);
	init_philos(data);
	return (1);
}
