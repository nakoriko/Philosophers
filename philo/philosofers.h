/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:56:17 by nakoriko          #+#    #+#             */
/*   Updated: 2024/11/12 08:33:52 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct	s_main;

typedef struct s_data
{
	int				n;
	int				id;
	int				i;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				eat_num;
	int				eat_counter;
	long long		last_eat;
	int				right_fork;
	int				left_fork;
	pthread_mutex_t	mutex_lasteat;
	struct s_main	*main;

}	t_philo_data;

typedef struct s_main
{
	int				index_d;
	int				index_eat;
	int				n;
	int				i;
	int				ac;
	char			**av;
	long long		time_to_die;
	pthread_t		*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	index;
	pthread_mutex_t	counter;
	t_philo_data	*data;
}	t_main;

int			ft_atoi(const char *nptr);
int			ft_checker(int ac, char **av);
void		*ft_func(void *data);
int			ft_main_init(t_main *main, int ac, char **av);
int			ft_mallocs(t_main *main);
void		ft_usleep(long int time);
long int	ft_time(void);
int			ft_fill_data(t_main *main, int ac, char **av);
void		ft_unlock_forks(t_philo_data *p_data);
long long	ft_atoi_super(const char *nptr);