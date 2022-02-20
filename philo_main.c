/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:39:07 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/20 20:38:48 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*clear_fork_array(t_fork ***forks)
{
	int	i;

	i = -1;
	while (forks && (*forks)[++i])
	{
		free((*forks)[i]);
		(*forks)[i] = NULL;
	}
	*forks = NULL;
	return (NULL);
}

void	*clear_philo_array(t_philo ***philos)
{
	int	i;

	i = -1;
	while (philos && (*philos)[++i])
	{
		free((*philos)[i]->small);
		free((*philos)[i]->big);
		free((*philos)[i]);
		(*philos)[i] = NULL;
	}
	*philos = NULL;
	return (NULL);
}

t_fork	**init_forks(int num_of_forks)
{
	t_fork	**forks;
	t_fork	*fork;

	forks = (t_fork **)malloc(sizeof(t_fork *) * (num_of_forks + 1));
	if (!forks)
		return (NULL);
	memset(forks, 0, sizeof(t_fork *) * (num_of_forks + 1));
	while (num_of_forks-- > 0)
	{
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork)
			return (clear_fork_array(&forks));
		fork->index = num_of_forks + 1;
		if (pthread_mutex_init(&fork->mutex, NULL))
			return (clear_fork_array(&forks));
		forks[num_of_forks] = fork;
	}
	return (forks);
}

t_philo	**init_philos(int num_of_philos, t_fork **forks)
{
	t_philo	**philos;
	t_philo	*philo;
	int		check;

	check = -1;
	philos = (t_philo **)malloc(sizeof(t_philo *) * (num_of_philos + 1));
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(t_philo *) * (num_of_philos + 1));
	while (num_of_philos-- > 0)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (clear_philo_array(&philos));
		philo->id = num_of_philos + 1;
		if (check == -1)
			philo->small = forks[0];
		else
			philo->small = forks[num_of_philos];
		philo->big = forks[num_of_philos + 1 + check];
		check = 0;
		philos[num_of_philos] = philo;
	}
	return (philos);
}

int	validate_arguments(int argc, char **argv)
{
	// check for each argument;
	(void)argc;
	(void)argv;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fork	**forks;
	t_philo	**philos;
	int	i = -1;

	if (argc != 6 || validate_arguments(argc - 1, &argv[1]))
		return (EXIT_FAILURE);
	forks = init_forks(atoi(argv[1])); // get my own atoi;
	philos = init_philos(atoi(argv[1]), forks);
	if (!forks || !philos)
		return (EXIT_FAILURE); // clear both?;
	while (philos[++i])
	{
		printf("Philo id %d\nSmall %d\t\tBig %d\n", philos[i]->id, philos[i]->small->index, philos[i]->big->index);
	}
	return (EXIT_SUCCESS);
}
