#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

long long ft_time(long long time);
typedef struct thread {

	pthread_t		t;
	pthread_mutex_t	lock;
	long long  		start;
	time_t			end;
	int				id;
	struct thread 	*next;
	long long		time_to_die;
	// int				time_to_eat;
	// int		 		time_to_sleep;
	// int	 	 	 	num_of_eat;
} s_thread;

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
		exit(printf("Error\n"));
	while (s[i])
	{
		num *= 10;
		num += s[i] - '0';
		i++;
	}
	return (num * signe);

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

void	*fct(void *x)
{
	s_thread *thread = (s_thread*)x;
	while (ft_time(thread->start) < thread->time_to_die)
	{
		pthread_mutex_lock(&thread->lock);
		printf("thread %d take the left fork\n", thread->id);
		pthread_mutex_lock(&thread->next->lock);
		printf("thread %d take the right fork\n", thread->id);
		pthread_mutex_unlock(&thread->lock);
		pthread_mutex_unlock(&thread->next->lock);
		usleep(100);
	}
	return (NULL);
}

void	struct_init(s_thread **ph, int num)
{
	int			i;
	s_thread	*t;

	i = 0;
	t = malloc(sizeof(s_thread));
	t->id = 0;
	while (i < num)
	{
		pthread_mutex_init(&t->lock, NULL);
		i++;
		t->id = i;
		t->next = NULL;
		ft_lstadd(ph, t);
		t = malloc(sizeof(s_thread));
	}
	ft_last(*ph)->next = *ph;
	free(t);
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		long long	start;
		s_thread	*ph;
		int			i;
		
		i = 0;
		struct_init(&ph, ft_atoi(av[1]));
		start = ft_time(0);
		while (i++ < ft_atoi(av[1]))
		{
			ph->time_to_die = ft_atoi(av[2]);
			ph->start = start;
			pthread_create(&ph->t, NULL, &fct, ph);
			usleep(50);
			ph = ph->next;
		}
		while(1);
		i = 0;
	}
}


























		// while (1)
		// {
		// 	long long end = ft_time(start);
		// 	if (end > (long long)ft_atoi(av[2]))
		// 	{
		// 		printf("philo %d is dead\n", ph->id);
		// 		return (1);
		// 	}
		// }
		// while (i++ < ft_atoi(av[1]))
		// {
		// 	pthread_join(ph->t, NULL);
		// 	ph = ph->next;
		// }