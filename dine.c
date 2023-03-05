/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:25:39 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:51:07 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	p_eat(t_philo *philo)
{
	if (philo->full == true || philo->args->kill_all == true)
		return ;
	if (philo->lt_eaten == 0)
	{
		gettime(philo->args);
		philo->lt_eaten = philo->args->ts_ms;
	}
	philo->lt_eaten = philo->args->ts_ms;
	if (philo->args->kill_all == false)
	{
		sem_wait(philo->args->semaphore->res_mgr);
		paction(pick_fork, philo);
		sem_wait(philo->args->semaphore->res_mgr);
		paction(pick_fork, philo);
		paction(eat, philo);
		philo->args->test_value += 1;
		usleep(philo->args->t_eat * 1000);
		gettime(philo->args);
		philo->lt_eaten = philo->args->ts_ms;
		philo->t_eaten++;
	}
}

static void	p_sleep(t_philo *philo)
{
	if (philo->args->kill_all == false)
	{
		sem_post(philo->args->semaphore->res_mgr);
		sem_post(philo->args->semaphore->res_mgr);
		paction(sleeping, philo);
		usleep(philo->args->t_sleep * 1000);
	}
}

static void	p_think_or_die(t_philo *philo)
{
	if (philo->full == true || philo->args->kill_all == true)
		return ;
	paction(think, philo);
}

void	*dine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	while (1)
	{
		if (philo->args->kill_all == true || philo->full == true)
		{
			sem_post(philo->args->semaphore->res_mgr);
			sem_post(philo->args->semaphore->res_mgr);
			return (NULL);
		}
		else
		{
			p_eat(philo);
			p_sleep(philo);
			p_think_or_die(philo);
		}
	}
	return (NULL);
}
