/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:57:35 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/04 12:06:50 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager(void *pointer);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

void	*manager(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->obj->t_eat - 10);
	while (is_died(philo->obj) == 0)
	{
		if (ft_eat(philo) == 0)
			break ;
		if (is_died(philo->obj) == 1)
			break ;
		if (ft_sleep(philo) == 0)
			break ;
		if (is_died(philo->obj) == 1)
			break ;
		if (ft_think(philo) == 0)
			break ;
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	int	my_fork;
	int	right_fork;

	if (is_died(philo->obj) == 1)
		return (0);
	my_fork = (philo->id - 1) % philo->obj->philo_mems;
	right_fork = philo->id % philo->obj->philo_mems;
	if (pthread_mutex_lock(&philo->obj->forks[my_fork]) == 0)
	{
		if (pthread_mutex_lock(&philo->obj->forks[right_fork]) == 0)
		{
			if (is_died(philo->obj) == 1)
			{
				pthread_mutex_unlock(&philo->obj->forks[my_fork]);
				pthread_mutex_unlock(&philo->obj->forks[right_fork]);
				return (0);
			}
			pthread_mutex_lock(&philo->eat_mutex);
			ft_print(*philo, EAT);
			ft_usleep(philo->obj->t_eat);
			update_last_time_meal(philo);
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_unlock(&philo->obj->forks[my_fork]);
			pthread_mutex_unlock(&philo->obj->forks[right_fork]);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->obj->forks[my_fork]);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (is_died(philo->obj) == 1)
		return (0);
	ft_print(*philo, SLEEP);
	ft_usleep(philo->obj->t_sleep);
	return (1);
}

int	ft_think(t_philo *philo)
{
	if (is_died(philo->obj) == 1)
		return (0);
	ft_print(*philo, THINK);
	return (1);
}


