/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:31:42 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/07 16:29:31 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_sem	*semaphore_init(void)
{
	t_sem	*semaphore;

	semaphore = (t_sem *)malloc(sizeof(t_sem));
	return (semaphore);
}

void	destroy_semaphores(t_args *args)
{
	free (args->semaphore);
}
