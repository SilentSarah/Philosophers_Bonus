/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:43:23 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:54:37 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
	{
		printf(GUIDE);
		return (0);
	}
	initialize_data(&args, av);
	load_philosopher_data(&args);
	fork_processes(&args);
	check_for_dead_philosophers(&args);
	return (0);
}
