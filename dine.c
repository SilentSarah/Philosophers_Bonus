/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:57:01 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/07 17:05:32 by hmeftah          ###   ########.fr       */
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
	msleep(args->t_eat);
	philo->lt_eaten = gettime();
	philo->t_eaten++;
}

static void	p_sleep(t_philo *philo, t_args *args)
{
	sem_post(args->semaphore->res_mgr);
	sem_post(args->semaphore->res_mgr);
	paction(sleeping, philo);
	msleep(args->t_sleep);
	paction(think, philo);
}

void	*monitor(void *context)
{
	t_philo		*philo;
	long long	ts_ms;

	philo = (t_philo *)context;
	while (1)
	{
		ts_ms = gettime();
		if (ts_ms - philo->lt_eaten >= philo->args->t_die
			&& philo->full == false)
		{
			paction(die, philo);
			sem_post(philo->args->semaphore->death);
			exit (0);
		}
	}
}

void	dine(t_philo *philo, t_args *args)
{
	while (1)
	{
		p_eat(philo, args);
		p_sleep(philo, args);
		if (philo->args->nt_eat > 0)
		{
			if (philo->t_eaten >= philo->args->nt_eat)
			{
				philo->full = true;
				sem_post(philo->args->semaphore->food_count);
			}
		}
	}
}
