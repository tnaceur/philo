/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:10:12 by tnaceur           #+#    #+#             */
/*   Updated: 2022/09/08 14:14:55 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm(t_thread *t)
{
	pthread_mutex_lock(&t->lock);
	printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
	pthread_mutex_lock(&t->next->lock);
	printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
	if (t->data->time_to_die >= ft_time(t->data->start) - t->last_meal)
	{
		pthread_mutex_lock(&t->data->eat);
		t->eat++;
		pthread_mutex_unlock(&t->data->eat);
		ft_eat(t, t->eat);
	}
}

void	*routine(void *ph)
{
	t_thread	*t;

	t = (t_thread *)ph;
	t->eat = 0;
	t->last_meal = 0;
	while (1)
	{
		norm(t);
		pthread_mutex_unlock(&t->lock);
		pthread_mutex_unlock(&t->next->lock);
		if (t->data->time_to_die >= ft_time(t->data->start) - t->last_meal)
			ft_sleep(t);
		if (t->data->time_to_die >= ft_time(t->data->start) - t->last_meal)
			printf("%lld %d is thinking\n", ft_time(t->data->start), t->id);
		else
			return (0);
	}
	return (0);
}

void	data_init(t_data *data, char **av)
{
	pthread_mutex_init(&data->eat, NULL);
	data->number_of_philo = ft_atoi(av[1]);
	data->start = ft_time(0);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_eat = ft_atoi(av[5]);
	else
		data->number_of_eat = -1;
}

void	struct_init(t_thread **ph, char **av)
{
	int			i;
	t_thread	*t;
	t_data		*data;

	i = 0;
	t = malloc(sizeof(t_thread));
	data = malloc(sizeof(t_data));
	data_init(data, av);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&t->lock, NULL);
		i++;
		t->id = i;
		t->data = data;
		t->next = NULL;
		ft_lstadd(ph, t);
		t = malloc(sizeof(t_thread));
	}
	ft_last(*ph)->next = *ph;
	free(t);
}

int	main(int ac, char **av)
{
	t_thread	*ph;
	int			i;

	if (check_args(av) && (ac == 5 || ac == 6)
		&& ft_atoi(av[1]) > 0 && ft_atoi(av[2]) > 0
		&& ft_atoi(av[3]) > 0 && ft_atoi(av[4]) > 0)
	{
		i = 0;
		ph = NULL;
		struct_init(&ph, av);
		while (i++ < ft_atoi(av[1]))
		{
			pthread_create(&ph->t, NULL, &routine, ph);
			pthread_detach(ph->t);
			ph = ph->next;
			usleep(100);
		}
		if (check_dead(ph))
			return (1);
	}
}
