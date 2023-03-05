/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:40:38 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/05 18:25:52 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define GUIDE "./philo <Number of Philosophers> <Time to die> <Time to eat> \
<Time to sleep> <OPTIONAL: Number of times each philosopher will eat>\n"

# define SEM_ERR "Error: Creation of a semaphore for this process has failed.\n"
# define PRC_ERR "Error: Cannot Fork Processes.\n"
# define ALOC_ERR "Error: Cannot Alocate Resources for a philosopher\n"

enum e_actions {
	eat,
	sleeping,
	think,
	pick_fork,
	die,
};

enum e_error_types {
	aloc,
	sem,
	forking,
};

struct s_semaphores {
	sem_t	*msgr;
	sem_t	*res_mgr;
	sem_t	*death;
};
typedef struct s_semaphores	t_sem;

struct s_args {
	pid_t			pid;
	t_sem			*semaphore;
	int				n_philos;
	int				t_die;
	int				philo_id;
	int				*pids;
	int				t_eat;
	int				t_sleep;
	int				nt_eat;
	long long		ts_ms;
	bool			kill_all;
	struct timeval	time;
	int				e_philos;
	int				test_value;
};
typedef struct s_args		t_args;

struct s_philo {
	int				id;
	long long		lt_eaten;
	long long		f_eaten;
	int				t_eaten;
	pthread_t		thread;
	t_args			*args;
	bool			die;
	bool			full;
};
typedef struct s_philo		t_philo;

int		_atoi(const char *str);
void	gettime(t_args *args);
void	perror(const char *error_msg);
void	paction(int type, t_philo *philo);
void	*dine(void *context);
void	monitor_philosopher(t_philo *philo, t_args *args);
void	exitprogram(t_args *args, int type);
void	initialize_data(t_args *args, char **av);
void	load_philosopher_data(t_args *args);
void	fork_processes(t_args *args);
void	create_philosophers(t_args *args);
void	initialize_semaphores(t_args *args);
void	check_for_dead_philosophers(t_args *args);
void	msleep(unsigned int ml_sec, t_args *args);
#endif