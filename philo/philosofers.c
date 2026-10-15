/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:14:44 by nakoriko          #+#    #+#             */
/*   Updated: 2024/11/12 08:38:43 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	ft_checker(int ac, char **av)
{
	int				i;
	struct timeval	time;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong numbers of arguments\n");
		return (1);
	}
	while (++i < ac)
	{
		if (ft_atoi_super(av[i]) <= 0)
		{
			printf("Argument %d has an error\n", i);
			return (1);
		}
		else if (ft_atoi(av[1]) == 1)
		{
			printf("%ld %d has taken a fork\n", ft_time(), 0);
			usleep(ft_atoi(av[2]) * 1000);
			printf("%ld %d died\n", ft_time(), 0);
			return (1);
		}
	}
	return (0);
}

int	ft_death_checker(int i, t_main *main)
{
	if ((ft_time() - main->data[i].last_eat) >= (main->time_to_die))
	{
		pthread_mutex_lock (&main->print);
		if (main->data[i].eat_num == 0)
		{
			pthread_mutex_unlock (&main->print);
			pthread_mutex_unlock(&main->data[i].mutex_lasteat);
			return (0);
		}
		pthread_mutex_unlock (&main->print);
		pthread_mutex_lock (&main->print);
		main->index_d = 1;
		pthread_mutex_unlock (&main->print);
		pthread_mutex_lock (&main->index);
		printf("%ld %d died\n", ft_time(), main->data[i].id);
		pthread_mutex_unlock (&main->index);
		pthread_mutex_unlock(&main->data[i].mutex_lasteat);
		return (0);
	}
	return (1);
}

void	ft_loop(t_main *main)
{
	int	i;
	int	j;

	j = 0;
	while (main->index_d == 0)
	{
		i = -1;
		while (++i < main->n)
		{
			pthread_mutex_lock(&main->data[i].mutex_lasteat);
			if (ft_death_checker(i, main) == 0)
			{
				j = 1;
				break ;
			}
			pthread_mutex_unlock(&main->data[i].mutex_lasteat);
		}
		if (j == 1)
			break ;
	}
}

void	ft_cleaner(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n)
		pthread_join(main->philosopher[i], NULL);
	pthread_mutex_destroy(&main->data->mutex_lasteat);
	pthread_mutex_destroy(&main->print);
	pthread_mutex_destroy(&main->counter);
	pthread_mutex_destroy(&main->index);
	free (main->data);
	free (main->philosopher);
	i = -1;
	while (++i < main->n)
		pthread_mutex_destroy(&main->forks[i]);
	free (main->forks);
}

int	main(int ac, char **av)
{
	t_main	main;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (ft_checker(ac, av) != 0)
		return (1);
	if (ft_main_init(&main, ac, av) == 1)
		return (1);
	while (i < main.n)
	{
		main.data[i].main = &main;
		pthread_create((&main.philosopher[i]), NULL, ft_func, &main.data[i]);
		i++;
	}
	ft_loop(&main);
	ft_cleaner(&main);
	return (0);
}
