/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_prep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:14:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/02 20:36:17 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	clear_philo(t_philo **philo)
{
	if (*philo)
	{
		free((*philo)->data);
		free(*philo);
		*philo = NULL;
	}
	return (0);
}

int	init_philo(t_data *data, t_philo **philo)
{
	(*philo) = (t_philo *)malloc(sizeof(t_philo));
	if (!(*philo))
		return (1);
	(*philo)->data = data;
	(*philo)->num_ate = 0;
	(*philo)->process_id = 0;
	(*philo)->thread_id = 0;
	(*philo)->t_ate = ft_get_time();
	sem_unlink("forks");
	(*philo)->forks_sem = sem_open("forks", O_CREAT,
			0644, (*philo)->data->total_philos);
	if ((*philo)->forks_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	sem_unlink("num_ate");
	(*philo)->num_ate_sem = sem_open("num_ate", O_CREAT, 0644, 1);
	if ((*philo)->num_ate_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	return (0);
}

int	validate_arguments(int total_arguments, char **arguments, t_data **data)
{
	if (ft_strlen(arguments[0]) > 8 || ft_strlen(arguments[1]) > 10
		|| ft_strlen(arguments[2]) > 10 || ft_strlen(arguments[3]) > 10)
		return (1);
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->total_philos = (int)ft_atoi(arguments[0]);
	(*data)->t_to_sleep = ft_atoi(arguments[3]);
	(*data)->t_to_die = ft_atoi(arguments[1]);
	(*data)->t_to_eat = ft_atoi(arguments[2]);
	(*data)->number_to_eat = -1;
	sem_unlink("fildes");
	(*data)->filedes_sem = sem_open("fildes", O_CREAT, 0644, 1);
	if ((*data)->filedes_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	if (total_arguments == 5)
		(*data)->number_to_eat = (int)ft_atoi(arguments[4]);
	return (0);
}
