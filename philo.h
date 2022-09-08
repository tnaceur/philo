/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:31:30 by tnaceur           #+#    #+#             */
/*   Updated: 2022/09/08 14:31:32 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data {
	long long				time_to_eat;
	long long				start;
	long long				time_to_die;
	long long				time_to_sleep;
	long long				number_of_eat;
	long long				number_of_philo;
	pthread_mutex_t			eat;
}	t_data;

typedef struct thread {
	pthread_t		t;
	pthread_mutex_t	lock;
	int				id;
	int				eat;
	struct thread	*next;
	t_data			*data;
	long long		last_meal;
}	t_thread;

long long	ft_time(long long time);
int			check_args(char **args);
void		ft_eat(t_thread *t, int eat);
long long	ft_atoi(char *s);
void		ft_sleep(t_thread *t);
void		my_usleep(t_thread *ph, long long time);
int			check_dead(t_thread *ph);
void		ft_lstadd(t_thread **t, t_thread *thread);
t_thread	*ft_last(t_thread *t);

#endif