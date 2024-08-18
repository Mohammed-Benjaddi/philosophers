/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:54:27 by mben-jad          #+#    #+#             */
/*   Updated: 2024/08/18 15:59:15 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_ate(t_data *data)
{
	int		counter;
	int		i;
	t_philo	*philos;

	counter = 0;
	i = 0;
	philos = data->philos;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&philos[i].is_eating);
		if (philos[i].eat_count >= data->times_to_eat)
			counter++;
		pthread_mutex_unlock(&philos[i].is_eating);
		i++;
		usleep(100);
	}
	if (counter == data->n_philos)
	{
		pthread_mutex_lock(&data->all_ate_mutex);
		data->all_philos_ate = 1;
		pthread_mutex_unlock(&data->all_ate_mutex);
		return (1);
	}
	return (0);
}

void	check_dead_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philos;
	while (++i < data->n_philos && data->all_philos_ate != 1)
	{
		pthread_mutex_lock(&philos[i].check_meal);
		if (get_current_time()
			- philos[i].last_meal >= philos[i].data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].check_meal);
			pthread_mutex_lock(&philos[i].data->dead_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&philos[i].data->dead_mutex);
			pthread_mutex_lock(&philos[i].data->print);
			printf("%s%lld %d died%s\n", RED, get_current_time()
				- philos[i].data->start_time, philos[i].id, NC);
			pthread_mutex_unlock(&philos[i].data->print);
			break ;
		}
		pthread_mutex_unlock(&philos[i].check_meal);
	}
	if (data->times_to_eat != -1 && philos_ate(data))
		return ;
}

void	destroy_all_forks(t_data *data, int size)
{
	int				i;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	i = 0;
	forks = data->forks;
	philos = data->philos;
	while (i < data->n_philos)
		pthread_join(data->philos[i++].thread, NULL);
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].is_eating);
		pthread_mutex_destroy(&philos[i].check_meal);
		i++;
	}
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->print);
	free(forks);
	free(philos);
}

static	int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (1);
}

void	*philo_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	ft_think(philo);
	if (philo->id % 2 == 0)
		ft_wait(philo->data->time_to_eat / 2);
	while (1)
	{
		if (!is_philo_dead(philo))
			break ;
		pthread_mutex_lock(&philo->data->all_ate_mutex);
		if (philo->data->all_philos_ate == 1)
		{
			pthread_mutex_unlock(&philo->data->all_ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->all_ate_mutex);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		usleep(100);
	}
	return (NULL);
}
