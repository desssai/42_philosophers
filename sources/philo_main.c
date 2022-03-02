/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:39:07 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/02 00:16:22 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->t_ate = ft_get_time();
	if (philo->data->number_to_eat)
		philo->num_ate++;
	pthread_mutex_unlock(&philo->mutex);
}

static void	*thinkeatsleep(void *data)
{
	t_philo	*philo;

	philo = data;
	philo->num_ate = 0;
	if (!(philo->id % 2))
		usleep(50);
	while (true)
	{
		pthread_mutex_lock(&philo->small->mutex);
		ft_say(I_TOOK_FORK, philo);
		pthread_mutex_lock(&philo->big->mutex);
		ft_say(I_TOOK_FORK, philo);
		ft_eat(philo);
		ft_say(IM_EATING, philo);
		ft_usleep(philo->data->t_to_eat);
		pthread_mutex_unlock(&philo->big->mutex);
		pthread_mutex_unlock(&philo->small->mutex);
		ft_say(IM_SLEEPING, philo);
		if (philo->data->number_to_eat != -1
			&& philo->data->number_to_eat == philo->num_ate)
			break ;
		ft_usleep(philo->data->t_to_sleep);
		ft_say(IM_THINKING, philo);
	}
	return (NULL);
}

static int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (ft_get_time() - philo->t_ate > philo->data->t_to_die)
	{
		if (philo->data->number_to_eat != -1
			&& philo->data->number_to_eat == philo->num_ate)
			return (1);
		pthread_mutex_lock(&philo->data->fd_mutex);
		printf("%lld %d has died.\n", ft_get_time(), philo->id);
		return (2);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

static int	serve_the_table(t_philo **philos)
{
	int	i;
	int	j;
	int	r;

	i = -1;
	while (philos[++i])
	{
		philos[i]->t_ate = ft_get_time();
		pthread_create(&philos[i]->thread_id, NULL, thinkeatsleep, philos[i]);
		pthread_detach(philos[i]->thread_id);
	}
	while (true)
	{
		i = -1;
		while (philos[++i])
		{
			r = check_if_dead(philos[i]);
			if (r == 2)
				return (0);
			else if (r == 1)
				j++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fork			**forks;
	t_philo			**philos;
	t_data			*data;

	if (argc > 6 || argc < 5)
		return (EXIT_FAILURE);
	if (validate_arguments(argc - 1, &argv[1], &data)
		|| init_forks(data->total_philos, &forks)
		|| init_philos(data, forks, &philos))
		return (EXIT_FAILURE);
	serve_the_table(philos);
	clear_philo_array(&philos, &forks);
	return (EXIT_SUCCESS);
}
