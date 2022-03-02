/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:14:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/01 23:42:40 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	clear_fork_array(t_fork ***forks)
{
	int	i;

	i = -1;
	while (forks && (*forks)[++i])
	{
		free((*forks)[i]);
		(*forks)[i] = NULL;
	}
	free(*forks);
	*forks = NULL;
	return (1);
}

int	clear_philo_array(t_philo ***philos, t_fork ***forks)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (philos && (*philos)[++j])
		;
	while (philos && (*philos)[++i])
	{
		if (i != j - 1)
			free((*philos)[i]->big);
		else
		{
			free((*philos)[i]->small);
			free((*philos)[i]->data);
		}
		free((*philos)[i]);
		(*philos)[i] = NULL;
	}
	free(*philos);
	free(*forks);
	*forks = NULL;
	*philos = NULL;
	return (1);
}

int	init_forks(int num_of_forks, t_fork ***forks)
{
	t_fork	*fork;

	*forks = (t_fork **)malloc(sizeof(t_fork *) * (num_of_forks + 1));
	if (!(*forks))
		return (1);
	memset((*forks), 0, sizeof(t_fork *) * (num_of_forks + 1));
	while (num_of_forks-- > 0)
	{
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork)
			return (clear_fork_array(forks));
		fork->index = num_of_forks + 1;
		if (pthread_mutex_init(&fork->mutex, NULL))
			return (clear_fork_array(forks));
		(*forks)[num_of_forks] = fork;
	}
	return (0);
}

int	init_philos(t_data *data, t_fork **forks, t_philo ***philos)
{
	t_philo	*philo;
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	*philos = (t_philo **)malloc(sizeof(t_philo *) * (data->total_philos + 1));
	if (!(*philos))
		return (1);
	memset(*philos, 0, sizeof(t_philo *) * (data->total_philos + 1));
	while (++i[0] < data->total_philos)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (clear_philo_array(philos, &forks));
		pthread_mutex_init(&philo->mutex, NULL);
		philo->id = i[0] + 1;
		philo->data = data;
		if (i[0] == data->total_philos - 1 && !i[1]--)
			philo->small = forks[0];
		else
			philo->small = forks[i[0]];
		philo->big = forks[i[0] + 1 + i[1]];
		(*philos)[i[0]] = philo;
	}
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
	pthread_mutex_init(&(*data)->fd_mutex, NULL);
	if (total_arguments == 5)
		(*data)->number_to_eat = (int)ft_atoi(arguments[4]);
	return (0);
}
