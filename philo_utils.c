/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:31:10 by tnaceur           #+#    #+#             */
/*   Updated: 2022/09/08 14:31:12 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(t_thread *ph, long long time)
{
	long long	current_time;

	current_time = ft_time(ph->data->start) + time;
	while (current_time > ft_time(ph->data->start))
		usleep(100);
}

void	ft_sleep(t_thread *t)
{
	printf("%lld %d is sleeping\n", ft_time(t->data->start), t->id);
	my_usleep(t, t->data->time_to_sleep);
}

long long	ft_atoi(char *s)
{
	long long	i;
	long long	num;
	int			signe;

	i = 0;
	signe = 1;
	num = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = -1;
		i++;
	}
	if (s[i] == '-' || s[i] == '+')
		return (-1);
	while (s[i])
	{
		num *= 10;
		num += s[i] - '0';
		i++;
	}
	return (num * signe);
}

void	ft_eat(t_thread *t, int eat)
{
	pthread_mutex_lock(&t->data->eat);
	t->last_meal = ft_time(t->data->start);
	pthread_mutex_unlock(&t->data->eat);
	printf("%lld %d is eating #%d\n", ft_time(t->data->start), t->id, eat);
	my_usleep(t, t->data->time_to_eat);
}

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (args[5] && ft_atoi(args[5]) <= 0)
		return (0);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] >= '0' && args[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
