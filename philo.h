/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:36:59 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/20 19:59:49 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork {
	int		index;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo {
	t_fork	*small;
	t_fork	*big;
	int		id;
}	t_philo;

#endif /* __PHILO_H__ */