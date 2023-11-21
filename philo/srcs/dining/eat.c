/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:45 by tsishika          #+#    #+#             */
/*   Updated: 2023/11/20 14:08:34 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dining.h"

void	set_time_last_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_time_last_eaten);
	philo->time_last_eaten = get_time(0);
	pthread_mutex_unlock(&philo->mtx_time_last_eaten);
}

void	ft_increment_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_eat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mtx_eat_count);
}

int	ft_get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->mtx_eat_count);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->mtx_eat_count);
	return (eat_count);
}

void	*monitor_rat_count_limit(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (!is_exit(data))
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (ft_get_eat_count(&data->philos[i]) < data->eat_limit)
				break ;
			i++;
		}
		if (i == data->num_of_philo)
		{
			set_exit(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
