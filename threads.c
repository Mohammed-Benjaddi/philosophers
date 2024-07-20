/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:53 by mben-jad          #+#    #+#             */
/*   Updated: 2024/07/20 09:51:13 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	*only_one_philo(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	pthread_mutex_lock(&philo->check_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->check_meal);
	ft_wait(philo->data->time_to_die);
	return (NULL);
}

static	void	check_one_philo(t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[0];
	pthread_mutex_lock(&philo->check_meal);
	if (get_current_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->check_meal);
		pthread_mutex_lock(&data->dead_mutex);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_lock(&philo->data->print);
		printf("%s%lld %d died%s\n", RED, get_current_time()
			- philo->data->start_time, philo->id, NC);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->check_meal);
}

void	start_program(t_data *data)
{
	int	i;

	i = -1;
	if (data->n_philos == 1)
	{
		pthread_create(&data->philos[0].thread, NULL, only_one_philo,
			&data->philos[0]);
		while (!data->is_dead)
			check_one_philo(data);
	}
	else
	{
		while (++i < data->n_philos)
			pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]);
		while (!data->is_dead && data->all_philos_ate != 1)
			check_dead_philo(data);
	}
}
