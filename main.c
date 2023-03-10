/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:43:23 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 17:57:45 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	run_monitoring(t_args *args)
{
	pthread_create(&args->g_monitor, NULL, monitor_food, args);
	monitor_death(args);
	pthread_detach(args->g_monitor);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
	{
		printf(GUIDE);
		return (0);
	}
	initialize_data(&args, av);
	initialize_semaphores(&args);
	load_philosopher_data(&args);
	run_monitoring(&args);
	return (0);
}
