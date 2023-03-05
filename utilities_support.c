/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:24:24 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:53:49 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	exitprogram(t_args *args, int type)
{
	if (type == aloc)
		perror(ALOC_ERR);
	else if (type == sem)
		perror(SEM_ERR);
	else if (type == forking)
		perror(PRC_ERR);
	if (type == aloc || type == sem || type == forking)
	{
		if (args->pids)
			free (args->pids);
	}
	exit (1);
}

void	initialize_semaphores(t_args *args)
{
	sem_unlink("/forks");
	sem_unlink("/message");
	sem_unlink("/death");
	args->semaphore->res_mgr = sem_open("/forks",
			O_CREAT | O_EXCL, 0644, args->n_philos);
	args->semaphore->msgr = sem_open("/message", O_CREAT | O_EXCL, 0644, 1);
	args->semaphore->death = sem_open("/death",
			O_CREAT | O_EXCL, 0644, args->n_philos);
	if (args->semaphore->msgr == SEM_FAILED
		|| args->semaphore->res_mgr == SEM_FAILED)
		exitprogram(args, sem);
}

void	check_for_dead_philosophers(t_args *args)
{
	int	i;

	i = -1;
	sem_wait(args->semaphore->death);
	while (++i < args->n_philos)
		kill(args->pids[i], SIGKILL);
	sem_post(args->semaphore->death);
}

void	msleep(unsigned int ml_sec, t_args *args)
{
	long long	start;

	gettime(args);
	start = args->ts_ms;
	while (1)
	{
		gettime(args);
		if (args->ts_ms - start == ml_sec)
			return ;
	}
}
