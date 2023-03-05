/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:00:02 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:54:30 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	create_philosophers(t_args *args)
{
	t_philo	philo;

	philo.args = args;
	philo.id = args->philo_id;
	philo.die = false;
	philo.full = false;
	philo.lt_eaten = 0;
	gettime(philo.args);
	philo.f_eaten = philo.args->ts_ms;
	pthread_create(&philo.thread, NULL, &dine, &philo);
	sem_wait(philo.args->semaphore->death);
	monitor_philosopher(&philo, args);
	pthread_join(philo.thread, NULL);
	return ;
}

void	fork_processes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		args->pid = fork();
		if (args->pid == -1)
			exitprogram(args, forking);
		else if (args->pid == 0)
		{
			args->philo_id = i;
			create_philosophers(args);
		}
		else
			args->pids[i] = args->pid;
	}
}

void	load_philosopher_data(t_args *args)
{
	t_sem	semaphore;

	args->semaphore = &semaphore;
	args->pids = NULL;
	args->pids = (int *)malloc(sizeof(int) * args->n_philos);
	if (!args->pids)
		exitprogram(args, aloc);
}

void	initialize_data(t_args *args, char **av)
{
	args->n_philos = _atoi(av[1]);
	args->t_die = _atoi(av[2]);
	args->t_eat = _atoi(av[3]);
	args->t_sleep = _atoi(av[4]);
	if (av[5])
		args->nt_eat = _atoi(av[5]);
	else
		args->nt_eat = -1;
	if (args->n_philos <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0 || args->nt_eat == 0)
	{
		printf(GUIDE);
		return ;
	}
	args->kill_all = false;
	return ;
}
