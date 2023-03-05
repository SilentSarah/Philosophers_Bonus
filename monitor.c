/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:32:47 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:56:10 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	check_last_time_eaten(t_philo *philo, t_args *args)
{
	gettime(args);
	if (philo->lt_eaten == 0)
		philo->lt_eaten = args->ts_ms;
	else if (args->ts_ms - philo->lt_eaten >= args->t_die)
	{
		paction(die, philo);
		sem_post(args->semaphore->death);
	}
}

void	check_times_eaten(t_philo *philo, t_args *args)
{
	if (args->nt_eat > 0)
	{
		if (philo->t_eaten == args->nt_eat)
			philo->full = true;
	}
}

void	monitor_philosopher(t_philo *philo, t_args *args)
{
	while (1)
	{
		if (args->kill_all == true || philo->full == true)
			break ;
		check_last_time_eaten(philo, args);
		check_times_eaten(philo, args);
	}
	if (philo->full == true)
		exit(0);
}
