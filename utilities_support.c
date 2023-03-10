/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:24:24 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 18:05:37 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	exitprogram(int type, t_args *args)
{
	if (type == aloc)
		perror(ALOC_ERR);
	else if (type == sem)
		perror(SEM_ERR);
	else if (type == forking)
		perror(PRC_ERR);
	destroy_semaphores(args);
	exit (1);
}

void	initialize_semaphores(t_args *args)
{
	sem_unlink(SEMFORKS);
	sem_unlink(SEMMSG);
	sem_unlink(SEMDEATH);
	sem_unlink(SEMFOODCOUNT);
	args->semaphore = semaphore_init();
	args->semaphore->res_mgr = sem_open(SEMFORKS, O_CREAT
			| O_EXCL, 0644, args->n_philos);
	args->semaphore->msgr = sem_open(SEMMSG, O_CREAT | O_EXCL, 0644, 1);
	args->semaphore->death = sem_open(SEMDEATH, O_CREAT
			| O_EXCL, 0644, args->n_philos);
	args->semaphore->food_count = sem_open(SEMFOODCOUNT, O_CREAT
			| O_EXCL, 0644, args->n_philos);
}

void	*monitor_food(void *context)
{
	int		i;
	t_args	*args;

	i = -1;
	args = context;
	if (args->nt_eat > 0)
	{
		while (args->fuel > 0)
		{
			sem_wait(args->semaphore->food_count);
			args->fuel -= args->nt_eat;
			sem_post(args->semaphore->food_count);
			if (args->fuel <= 0)
			{
				while (++i < args->n_philos)
					kill (args->pids[i], SIGKILL);
				destroy_semaphores(args);
				exit (0);
			}
		}
	}
	return (NULL);
}

void	monitor_death(t_args *args)
{
	int	i;

	i = -1;
	sem_wait(args->semaphore->death);
	while (++i < args->n_philos)
		kill (args->pids[i], SIGKILL);
	sem_post(args->semaphore->death);
	destroy_semaphores(args);
	return ;
}
