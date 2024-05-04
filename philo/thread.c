/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:10:24 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/03 12:00:33 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->philo_mems)
	{
		pthread_create(&obj->threads[i], NULL, manager, &obj->philo[i]);
		i++;
	}
}

void	join_threads(t_obj *obj)
{
	int	i;

	i = 0;
	while(i < obj->philo_mems)
	{
		pthread_join(obj->threads[i], NULL);
		i++;
	}
}

void	free_mutexs(t_obj *obj)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&obj->died_mutex);
	while (i < obj->philo_mems)
	{
		pthread_mutex_destroy(&obj->forks[i]);
		pthread_mutex_destroy(&obj->philo[i].eat_mutex);
		pthread_mutex_destroy(&obj->philo[i].sleep_mutex);
		pthread_mutex_destroy(&obj->philo[i].meal_mutex);
		i++;
	}
}
