/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:13:31 by nakoriko          #+#    #+#             */
/*   Updated: 2024/11/12 08:40:50 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	ft_mallocs(t_main *main)
{
	main->philosopher = (pthread_t *) malloc(sizeof(pthread_t)
			* main->n);
	if (main->philosopher == NULL)
		return (1);
	memset(main->philosopher, 0, sizeof(pthread_t) * main->n);
	main->data = (t_philo_data *) malloc(sizeof(t_philo_data) * main->n);
	if (main->data == NULL)
	{
		free(main->philosopher);
		return (1);
	}
	memset(main->data, 0, sizeof(t_philo_data) * main->n);
	main->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* main->n);
	if (main->forks == NULL)
	{
		free(main->philosopher);
		free(main->data);
		return (1);
	}
	memset(main->forks, 0, sizeof(pthread_mutex_t) * main->n);
	return (0);
}

int	ft_fill_data(t_main *main, int ac, char **av)
{
	int				i;
	struct timeval	time;

	i = 0;
	while (i < main->n)
	{
		main->data[i].n = main->n;
		main->data[i].id = i + 1;
		main->data[i].i = 0;
		main->data[i].time_to_eat = ft_atoi(av[3]);
		main->data[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			main->data[i].eat_num = ft_atoi(av[5]);
		else
			main->data[i].eat_num = 2147483647;
		main->data[i].eat_counter = 0;
		main->data[i].right_fork = 0;
		main->data[i].left_fork = 0;
		if (pthread_mutex_init(&main->data[i].mutex_lasteat, NULL) != 0)
			return (0);
		main->data[i].last_eat = ft_time();
		i++;
	}
	return (1);
}

int	ft_main_init(t_main *main, int ac, char **av)
{
	int	i;

	i = 0;
	main->index_d = 0;
	main->index_eat = 0;
	main->n = ft_atoi(av[1]);
	main->ac = ac;
	main->av = av;
	main->time_to_die = ft_atoi(av[2]);
	if (ft_mallocs(main) == 1)
		return (1);
	while (i < main->n)
	{
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
	pthread_mutex_init (&main->print, NULL);
	pthread_mutex_init (&main->index, NULL);
	pthread_mutex_init (&main->counter, NULL);
	if (ft_fill_data(main, ac, av) == 0)
		return (1);
	return (0);
}
