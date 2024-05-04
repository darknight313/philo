/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:02:39 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/04 12:06:07 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_time_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_time_ml = current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	ft_print(t_philo philo, int n)
{
	if (n == SLEEP)
		printf("%ld %d is sleeping\n", current_time() - philo.obj->start, philo.id);
	else if (n == EAT)
		printf("%ld %d is eating\n", current_time() - philo.obj->start, philo.id);
	else if (n == DIED)
		printf("%ld %d died\n", current_time() - philo.obj->start, philo.id);
	else if (n == THINK)
		printf("%ld %d is thinking\n", current_time() - philo.obj->start, philo.id);
}
int	is_eating(t_obj *obj, int i)
{
	if (pthread_mutex_lock(&obj->philo[i].eat_mutex) == 0)
	{
		pthread_mutex_unlock(&obj->philo[i].eat_mutex);
		return (0);
	}
	return (1);
}
int	check_died(t_philo philo)
{
	if (current_time() - philo.last_time_ml >= philo.obj->t_die)
		return (1);
	return (0);
}

int	is_died(t_obj *obj)
{
	int	i;

	i = 0;
	if (obj->died == 1)
		return (1);
	pthread_mutex_lock(&obj->died_mutex);
	while (i < obj->philo_mems)
	{
		if (check_died(obj->philo[i]) == 1 && !is_eating(obj, i))
		{
			if (obj->died == 1)
			{
				pthread_mutex_unlock(&obj->died_mutex);
				return (1);
			}
			obj->died = 1;
			ft_print(obj->philo[i], DIED);
			pthread_mutex_unlock(&obj->died_mutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&obj->died_mutex);
	return (0);
}


