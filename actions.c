/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:18:16 by mben-jad          #+#    #+#             */
/*   Updated: 2024/07/19 18:19:24 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_msg(philo, YELLOW, "has taken a fork");
	print_msg(philo, YELLOW, "has taken a fork");
	print_msg(philo, GREEN, "is eating");
	pthread_mutex_lock(&philo->check_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->check_meal);
	ft_wait(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->is_eating);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->is_eating);
}

void	ft_think(t_philo *philo)
{
	print_msg(philo, MAGENTA, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, CYAN, "is sleeping");
	ft_wait(philo->data->time_to_sleep);
}
