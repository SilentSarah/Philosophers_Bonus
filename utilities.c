/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:00:31 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 17:31:31 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ((str[i] == '\t' || str[i] == '\n'
				|| str[i] == '\v' || str[i] == '\f'
				|| str[i] == '\r' || str[i] == ' ')))
			i++;
	return (i);
}

int	_atoi(const char *str)
{
	int	res;
	int	i;
	int	neg;

	i = spaces(str);
	neg = 1;
	res = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	return (res * neg);
}

void	gettime(t_args *args)
{
	gettimeofday(&args->time, NULL);
	args->ts_ms = ((long long)args->time.tv_sec * 1000)
		+ ((long long)args->time.tv_usec / 1000);
}

void	perror(const char *error_msg)
{
	int	i;

	i = -1;
	while (error_msg[++i])
		write(2, &error_msg, sizeof(char));
	return ;
}

void	paction(int type, t_philo *philo)
{
	//sem_wait(philo->args->semaphore->msgr);
	gettime(philo->args);
	if (type == pick_fork)
		printf("%lld %d has taken a fork\n",
			philo->args->ts_ms - philo->lt_eaten, philo->id + 1);
	else if (type == eat)
		printf("%lld %d is eating\n",
			philo->args->ts_ms - philo->f_eaten, philo->id + 1);
	else if (type == sleeping)
		printf("%lld %d is sleeping\n",
			philo->args->ts_ms - philo->f_eaten, philo->id + 1);
	else if (type == think)
		printf("%lld %d is thinking\n",
			philo->args->ts_ms - philo->f_eaten, philo->id + 1);
	else if (type == die)
		printf("%lld %d died\n",
			philo->args->ts_ms - philo->f_eaten, philo->id + 1);
	//sem_post(philo->args->semaphore->msgr);
}
