/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:40:38 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 17:58:56 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h> 
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>

// ERROR MESSAGES
# define GUIDE "./philo <Number of Philosophers> <Time to die> <Time to eat> \
<Time to sleep> <OPTIONAL: Number of times each philosopher will eat>\n"

# define SEM_ERR "Error: Creation of a semaphore for this process has failed.\n"
# define PRC_ERR "Error: Cannot Fork Processes.\n"
# define ALOC_ERR "Error: Cannot Alocate Resources for a philosopher\n"

// SEMAPHORE NAMES
# define SEMFORKS "/forks"
# define SEMHOLDFORKS "/heldforks"
# define SEMMSG "/message"
# define SEMDEATH "/death"

// ACTIONS IDS
enum e_actions {
	eat,
	sleeping,
	think,
	pick_fork,
	die,
};

// ERROR IDS
enum e_error_types {
	aloc,
	sem,
	forking,
};

// PHILOSOPHER DATA
struct s_semaphores {
	sem_t	*msgr;
	sem_t	*res_mgr;
	sem_t	*death;
	sem_t	*hforks;
};
typedef struct s_semaphores	t_sem;

struct s_args {
	pid_t			pid;
	t_sem			*semaphore;
	int				n_philos;
	int				t_die;
	int				philo_id;
	int				pids[2000];
	int				t_eat;
	int				t_sleep;
	int				nt_eat;
	long long		ts_ms;
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

// FUNCTIONS LIST
int		_atoi(const char *str);
void	gettime(t_args *args);
void	perror(const char *error_msg);
void	paction(int type, t_philo *philo);
void	dine(t_philo *philo, t_args *args);
void	exitprogram(int type);
void	initialize_data(t_args *args, char **av);
void	load_philosopher_data(t_args *args);
void	create_philosophers(t_args *args);
void	initialize_semaphores(t_args *args);
void	*monitor(void *context);
void	check_philosophers_status(t_args *args);
#endif