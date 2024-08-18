/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:55 by mben-jad          #+#    #+#             */
/*   Updated: 2024/08/18 15:59:08 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	printf("%sError: %s%s\n", RED, msg, NC);
}

int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_wait(int ms)
{
	int	start;

	(void)ms;
	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(200);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print_msg(t_philo *philo, char *color, char *description)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (!philo->data->is_dead)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%s%lld %d %s%s\n", color, get_current_time()
			- philo->data->start_time, philo->id, description, NC);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
}
