/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:57:01 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 17:25:46 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	p_eat(t_philo *philo, t_args *args)
{
	sem_wait(args->semaphore->res_mgr);
	paction(pick_fork, philo);
	sem_wait(args->semaphore->res_mgr);
	paction(pick_fork, philo);
	paction(eat, philo);
	usleep(args->t_eat * 1000);
	gettime(args);
	philo->lt_eaten = args->ts_ms;
	philo->t_eaten++;
}

static void	p_sleep(t_philo *philo, t_args *args)
{
	sem_post(args->semaphore->res_mgr);
	sem_post(args->semaphore->res_mgr);
	paction(sleeping, philo);
	usleep(args->t_sleep * 1000);
	paction(think, philo);
}

void	*monitor(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	while (1)
	{
		if (philo->args->nt_eat > 0)
			if (philo->t_eaten >= philo->args->nt_eat)
				exit (0);
		gettime(philo->args);
		if (philo->args->ts_ms - philo->lt_eaten >= philo->args->t_die)
		{
			sem_post(philo->args->semaphore->death);
			exit (0);
		}
	}
}

void	dine(t_philo *philo, t_args *args)
{
	while (1)
	{
		if (philo->full == true)
			exit (0);
		else
		{
			p_eat(philo, args);
			p_sleep(philo, args);
		}
	}
}
