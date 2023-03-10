/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:02:19 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 17:58:44 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	create_philosophers(t_args *args)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.args = args;
	philo.id = args->philo_id;
	philo.lt_eaten = args->ts_ms;
	philo.f_eaten = args->ts_ms;
	philo.t_eaten = 0;
	philo.full = false;
	sem_wait(args->semaphore->death);
	sem_wait(args->semaphore->food_count);
	pthread_create(&philo.thread, NULL, monitor, &philo);
	dine(&philo, args);
	pthread_join(philo.thread, NULL);
}

void	load_philosopher_data(t_args *args)
{
	int	i;

	i = -1;
	args->ts_ms = gettime();
	while (++i < args->n_philos)
	{
		args->pid = fork();
		if (args->pid == -1)
			exitprogram(forking, args);
		else if (args->pid == 0)
		{
			args->philo_id = i;
			create_philosophers(args);
			usleep(1000);
		}
		else if (args->pid > 0)
			args->pids[i] = args->pid;
	}
	usleep(1000);
}

void	initialize_data(t_args *args, char **av)
{
	args->n_philos = _atoi(av[1]);
	args->t_die = _atoi(av[2]);
	args->t_eat = _atoi(av[3]);
	args->t_sleep = _atoi(av[4]);
	args->e_philos = 0;
	if (av[5])
	{
		args->nt_eat = _atoi(av[5]);
		args->fuel = args->n_philos * args->nt_eat;
	}
	else
	{
		args->nt_eat = -1;
		args->fuel = 0;
	}
	if (args->n_philos <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0 || args->nt_eat == 0)
	{
		printf(GUIDE);
		return ;
	}
	return ;
}
