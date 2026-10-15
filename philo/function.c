/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:02:02 by nakoriko          #+#    #+#             */
/*   Updated: 2024/11/12 08:42:17 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	ft_check_index_d(t_philo_data *p_data)
{
	int	temp;

	pthread_mutex_lock(&p_data->main->index);
	temp = p_data->main->index_d;
	pthread_mutex_unlock(&p_data->main->index);
	return (temp);
}

void	ft_print(t_philo_data *p_data, char *str)
{
	pthread_mutex_lock (&p_data->main->print);
	if (ft_check_index_d(p_data) != 0)
	{
		pthread_mutex_unlock (&p_data->main->print);
		return ;
	}
	printf("%ld %d %s\n", ft_time(), p_data->id, str);
	pthread_mutex_unlock (&p_data->main->print);
}

void	*ft_eat(t_philo_data *p_data)
{
	ft_print(p_data, "has taken a fork");
	ft_print(p_data, "has taken a fork");
	ft_print(p_data, "is eating");
	pthread_mutex_lock (&p_data->main->print);
	p_data->eat_num--;
	pthread_mutex_unlock (&p_data->main->print);
	pthread_mutex_lock(&p_data->mutex_lasteat);
	p_data->last_eat = ft_time();
	pthread_mutex_unlock(&p_data->mutex_lasteat);
	ft_usleep(p_data->time_to_eat);
	ft_unlock_forks(p_data);
	ft_print(p_data, "is sleeping");
	ft_usleep (p_data->time_to_sleep);
	ft_print(p_data, "is thinking");
	pthread_mutex_lock (&p_data->main->print);
	if (p_data->main->index_d == 1)
	{
		pthread_mutex_unlock (&p_data->main->print);
		return (NULL);
	}
	pthread_mutex_unlock (&p_data->main->print);
	p_data->i = 0;
	return ((void *)1);
}

t_philo_data	*fork_index(t_philo_data *p)
{
	p->right_fork = p->id - 1;
	p->left_fork = p->id;
	if (p->id == (p->n))
	{
		p->right_fork = 0;
		p->left_fork = p->id - 1;
	}
	return (p);
}

void	*ft_func(void *data)
{
	t_philo_data			*p_data;

	p_data = (t_philo_data *)data;
	p_data = fork_index(p_data);
	if (p_data->id % 2 == 0)
		ft_usleep(100);
	while (p_data->eat_num)
	{
		if (p_data->i < 3)
			ft_usleep(1);
		pthread_mutex_lock (&p_data->main->forks[p_data->right_fork]);
		if (pthread_mutex_lock (&p_data->main->forks[p_data->left_fork]) == 0)
		{
			if (ft_eat(p_data) == NULL)
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock (&p_data->main->forks[p_data->right_fork]);
			if (p_data->i < 2)
				ft_usleep(1);
		}
		p_data->i++;
	}
	return (NULL);
}
