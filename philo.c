#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

long long ft_time(long long time);

typedef struct	t_data	{
	long long				dead;
	long long				time_to_eat;
	long long				start;
	long long				time_to_die;
	long long		 		time_to_sleep;
	long long	 	 	 	number_of_eat;
}	s_data;

typedef struct thread {

	pthread_t		t;
	pthread_mutex_t	lock;
	int				id;
	struct thread	*next;
	s_data			*data;
}	s_thread;




int	check_args(char **args)
{
	int	i;
	int	j;

	i = 1;
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

void	*routine(void *ph)
{
	s_thread	*t;
	int 		count;
	long long	last_meal;
	
	t = (s_thread*)ph;
	count  = 0;
	last_meal = t->data->start;
	while (1)
	{
		count = 0;
		if (!pthread_mutex_lock(&t->lock))
		{
			printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
			count++;
		}
		if (!pthread_mutex_lock(&t->next->lock))
		{
			printf("%lld %d has taken a fork\n", ft_time(t->data->start), t->id);
			count++;
		}
		if (count == 2)
		{
			printf("%lld %d is eating\n", ft_time(t->data->start), t->id);
			for (int i = 0; i < t->data->time_to_eat; i++)
				usleep(1000);
			last_meal = ft_time(t->data->start);
		}
		printf("%lld %d is thinking\n", ft_time(t->data->start), t->id);
		printf("%lld %d is sleeping\n", ft_time(t->data->start), t->id);
		if (t->data->time_to_die > ft_time(t->data->start) - last_meal)
		{
			t->data->dead = 1;
			printf("%lld %d is dead\n", ft_time(t->data->start), t->id);
		}
		if (t->data->dead == 1)
			return (NULL);
		for (int i = 0; i < t->data->time_to_sleep; i++)
			usleep(1000);
		pthread_mutex_unlock(&t->lock);
		pthread_mutex_unlock(&t->next->lock);
		for (int i = 0; i < 100; i++)
			usleep(1);
	}
	return (NULL);
}

void data_init(s_data *data, char **av)
{
	data->start = ft_time(0);
	data->dead = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_eat = ft_atoi(av[5]);
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
	if (check_args(av) && (ac == 5 || ac == 6) && ft_atoi(av[1]) > 0)
	{
		s_thread	*ph;
		int			i;
		long long	start;
		
		i = 0;
		struct_init(&ph, av);
		while (i++ < ft_atoi(av[1]))
		{
			pthread_create(&ph->t, NULL, &routine, &(*ph));
			usleep(500);
			ph = ph->next;
		}
		i = 0;
		while(i++ < ft_atoi(av[1]))
		{
			if (pthread_join(ph->t, NULL))
				return 0;
			ph = ph->next;
		}
	}
}
