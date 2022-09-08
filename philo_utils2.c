/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:14:35 by tnaceur           #+#    #+#             */
/*   Updated: 2022/09/08 14:14:40 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(long long time)
{
	struct timeval	hello;

	gettimeofday(&hello, 0);
	return ((hello.tv_sec * 1000) + (hello.tv_usec / 1000) - time);
}

t_thread	*ft_last(t_thread *t)
{
	t_thread	*tmp;

	if (!t)
		return (NULL);
	tmp = t;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd(t_thread **t, t_thread *thread)
{
	if (!*t)
		*t = thread;
	else
		ft_last(*t)->next = thread;
}

int	check_dead2(t_thread *ph)
{
	int	i;

	i = 0;
	while (ph->eat >= ph->data->number_of_eat && i < ph->data->number_of_philo)
	{
		ph = ph->next;
		i++;
	}
	if (i == ph->data->number_of_philo)
		return (0);
	return (1);
}

int	check_dead(t_thread *ph)
{
	while (ph)
	{
		if (ph->data->time_to_die < ft_time(ph->data->start) - ph->last_meal)
		{
			printf("%lld %d is dead\n", ft_time(ph->data->start), ph->id);
			return (1);
		}
		if (ph->data->number_of_eat != -1)
		{
			if (!check_dead2(ph))
				return (1);
		}
		usleep(200);
		ph = ph->next;
	}
	return (0);
}
