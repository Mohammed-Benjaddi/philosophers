/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:14:46 by mben-jad          #+#    #+#             */
/*   Updated: 2024/08/18 15:59:21 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (ft_error("Arguments must be 4 or 5"), 1);
	data = malloc(sizeof(t_data));
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
