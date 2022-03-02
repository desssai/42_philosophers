/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:36:59 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/01 23:39:21 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define I_TOOK_FORK "%lld %d has taken a fork.\n"
# define IM_SLEEPING "%lld %d is sleeping.\n"
# define IM_THINKING "%lld %d is thinking.\n"
# define IM_EATING "%lld %d is eating.\n"

typedef pthread_mutex_t	t_mutex;

typedef struct s_data {
	int			number_to_eat;
	int			total_philos;
	long long	t_to_sleep;
	long long	t_to_eat;
	long long	t_to_die;
	t_mutex		fd_mutex;
}	t_data;

typedef struct s_fork {
	int		index;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo {
	pthread_t	thread_id;
	int			num_ate;
	t_fork		*small;
	long long	t_ate;
	t_data		*data;
	t_mutex		mutex;
	t_fork		*big;
	int			id;
}	t_philo;

int			validate_arguments(int total_args, char **arguments, t_data **data);
int			init_philos(t_data *data, t_fork **forks, t_philo ***philos);
int			clear_philo_array(t_philo ***philos, t_fork ***forks);
int			init_forks(int num_of_forks, t_fork ***forks);
int			clear_fork_array(t_fork ***forks);

void		ft_say(const char *expression, t_philo *philo);
int			ft_strlen(const char *str);
void		ft_usleep(long long time);
long long	ft_atoi(const char *num);
long long	ft_get_time(void);

#endif /* __PHILO_H__ */