/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:05:20 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/04 12:15:27 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_values(t_obj *obj)
{
	obj->t_die = 0;
	obj->t_eat = 0;
	obj->t_sleep = 0;
	obj->start = 0;
	obj->philo_mems = 0;
	obj->died = 0;
	obj->meals_to_have = 0;
}

void	create_obj(t_obj *obj, char **argv)
{
	int	i;

	i = 0;
	if (ft_atoi(argv[5]) != 5)
		obj->meals_to_have = (int)ft_atoi(argv[5]);
	obj->start = current_time();
	obj->philo_mems = (int)ft_atoi(argv[1]);
	obj->t_die = ft_atoi(argv[2]);
	obj->t_eat = ft_atoi(argv[3]);
	obj->t_sleep = ft_atoi(argv[4]);
	obj->threads = malloc(sizeof(pthread_t) * obj->philo_mems);
	obj->philo = malloc(sizeof(t_philo) * obj->philo_mems);
	obj->forks = malloc(sizeof(pthread_mutex_t) * obj->philo_mems);
	pthread_mutex_init(&obj->died_mutex, NULL);
	while (i < obj->philo_mems)
	{
		obj->philo[i].id = i + 1;
		obj->philo[i].last_time_ml = current_time();
		pthread_mutex_init(&obj->forks[i], NULL);
		pthread_mutex_init(&obj->philo[i].eat_mutex, NULL);
		pthread_mutex_init(&obj->philo[i].sleep_mutex, NULL);
		pthread_mutex_init(&obj->philo[i].meal_mutex, NULL);
		obj->philo[i].obj = obj;
		i++;
	}
}
