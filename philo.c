/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:46 by mben-jad          #+#    #+#             */
/*   Updated: 2024/07/20 12:25:46 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (1);
	if (!parsing(av + 1))
	{
		free(data);
		return (ft_error("Arguments are not valid"), 1);
	}
	if (!init_program(av + 1, data))
	{
		free(data->forks);
		free(data->philos);
		free(data);
		return (ft_error("Something went wrong!"), 1);
	}
	start_program(data);
	destroy_all_forks(data, data->n_philos);
	free(data);
	return (0);
}
