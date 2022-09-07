/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:10:12 by tnaceur           #+#    #+#             */
/*   Updated: 2021/11/30 21:11:59 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

long long ft_time(long long time);

typedef struct	t_data	{
	long long				time_to_eat;
	long long				start;
	long long				time_to_die;
	long long		 		time_to_sleep;
	long long	 	 	 	number_of_eat;
	long long	 	 	 	number_of_philo;
	pthread_mutex_t			eat;
}	s_data;

typedef struct thread {

	pthread_t		t;
	pthread_mutex_t	lock;
	int				id;
	int				eat;
	struct thread	*next;
	s_data			*data;
	long long		 	 	last_meal;
}	s_thread;

void	my_usleep(s_thread *ph, long long time)
{
	long long	current_time;

	current_time = ft_time(ph->data->start)  + time;
	while (current_time > ft_time(ph->data->start))
		usleep(100);
}



void	ft_sleep(s_thread *t)
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

void	ft_eat(s_thread *t, int eat)
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


s_thread *ft_last(s_thread *t)
{
	s_thread	*tmp;

	if (!t)
		return (NULL);
	tmp = t;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void ft_lstadd(s_thread **t, s_thread *thread)
{
	if (!*t)
		*t = thread;
	else
		ft_last(*t)->next = thread;
}

void	*check_dead(void *t)
{
	s_thread *ph;

	ph = (s_thread*)t;
	while (ph)
	{
		if (ph->data->time_to_die < ft_time(ph->data->start) - ph->last_meal)
		{
			printf("%lld %d is dead\n", ft_time(ph->data->start), ph->id);
			return (NULL);
		}
		if (ph->data->number_of_eat != -1)
		{
			int	i;

			i = 0;
			while (ph->eat == ph->data->number_of_eat && i < ph->data->number_of_philo)
			{
				ph = ph->next;
				i++;
			}
			if (i == ph->data->number_of_philo)
				return (NULL);
		}
		usleep(200);
		ph = ph->next;
	}
	return (NULL);
}

void	*routine(void *ph)
{
	s_thread	*t;
	int 		count;
	
	t = (s_thread*)ph;
	count  = 0;
	t->eat  = 0;
	t->last_meal = 0;
	while (1)
	{
		count = 0;
		pthread_mutex_lock(&t->lock);
		printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
		count++;
		pthread_mutex_lock(&t->next->lock);
		printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
		count++;
		if (count == 2 && t->data->time_to_die >= ft_time(t->data->start) - t->last_meal)
		{
			pthread_mutex_lock(&t->data->eat);
			t->eat++;
			pthread_mutex_unlock(&t->data->eat);
			ft_eat(t, t->eat);
		}
		else
			return (0);
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

void data_init(s_data *data, char **av)
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


void	struct_init(s_thread **ph, char **av)
{
	int			i;
	s_thread	*t;
	s_data		*data;

	i = 0;
	t = malloc(sizeof(s_thread));
	data = malloc(sizeof(s_data));
	data_init(data, av);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&t->lock, NULL);
		i++;
		t->id = i;
		t->data = data;
		t->next = NULL;
		ft_lstadd(ph, t);
		t = malloc(sizeof(s_thread));
	}
	ft_last(*ph)->next = *ph;
	free(t);
}

int main(int ac, char **av)
{
	if (check_args(av) && (ac == 5 || ac == 6) &&
		ft_atoi(av[1]) > 0 && ft_atoi(av[2]) > 0 &&
		ft_atoi(av[3]) > 0 && ft_atoi(av[4]) > 0)
	{
		s_thread	*ph;
		int			i;
		long long	start;
		pthread_t	t;
		
		i = 0;
		ph = NULL;
		struct_init(&ph, av);
		while (i++ < ft_atoi(av[1]))
		{
			pthread_create(&ph->t, NULL, &routine, &(*ph));
			ph = ph->next;
			usleep(100);
		}
		pthread_create(&t, NULL, &check_dead, ph);
		pthread_join(t, NULL);
	}
}
