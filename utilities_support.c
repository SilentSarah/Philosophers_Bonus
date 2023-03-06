/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:24:24 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 17:37:23 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	exitprogram(int type)
{
	if (type == aloc)
		perror(ALOC_ERR);
	else if (type == sem)
		perror(SEM_ERR);
	else if (type == forking)
		perror(PRC_ERR);
	exit (1);
}

void	initialize_semaphores(t_args *args)
{
	t_sem	semaphore;

	memset(&semaphore, 0, sizeof(t_sem));
	sem_unlink(SEMFORKS);
	sem_unlink(SEMMSG);
	sem_unlink(SEMDEATH);
	semaphore.res_mgr = sem_open(SEMFORKS, O_CREAT
			| O_EXCL, 0644, args->n_philos);
	semaphore.msgr = sem_open(SEMMSG, O_CREAT | O_EXCL, 0644, 1);
	semaphore.death = sem_open(SEMDEATH, O_CREAT
			| O_EXCL, 0644, args->n_philos);
	args->semaphore = &semaphore;
}

void	check_philosophers_status(t_args *args)
{
	int	i;

	i = -1;
	sem_wait(args->semaphore->death);
	while (++i < args->n_philos)
		kill (args->pids[i], SIGKILL);
	exit (0);
}
