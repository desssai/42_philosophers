/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:39:07 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/02 23:30:47 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->num_ate_sem);
	philo->t_ate = ft_get_time();
	if (philo->data->number_to_eat)
		philo->num_ate++;
	sem_post(philo->num_ate_sem);
}

static void	*eatsleep(void *data)
{
	t_philo	*philo;

	philo = data;
	philo->num_ate = 0;
	if (!(philo->id % 2))
		usleep(50);
	while (true)
	{
		sem_wait(philo->forks_sem);
		ft_say(I_TOOK_FORK, philo);
		sem_wait(philo->forks_sem);
		ft_say(I_TOOK_FORK, philo);
		ft_eat(philo);
		ft_say(IM_EATING, philo);
		ft_usleep(philo->data->t_to_eat);
		ft_say(IM_SLEEPING, philo);
		sem_post(philo->forks_sem);
		sem_post(philo->forks_sem);
		if (philo->data->number_to_eat != -1
			&& philo->data->number_to_eat == philo->num_ate)
			break ;
		ft_usleep(philo->data->t_to_sleep);
		ft_say(IM_THINKING, philo);
	}
	return (NULL);
}

static int	ft_eat_alone(t_philo *philo)
{
	pthread_create(&philo->thread_id, NULL, eatsleep, philo);
	pthread_detach(philo->thread_id);
	while (true)
	{
		sem_wait(philo->num_ate_sem);
		if (ft_get_time() - philo->t_ate > philo->data->t_to_die)
		{
			if (philo->data->number_to_eat == philo->num_ate)
				return (2);
			sem_wait(philo->data->filedes_sem);
			printf(I_DIED, ft_get_time(), philo->id);
			return (1);
		}
		sem_post(philo->num_ate_sem);
	}
	return (0);
}

static int	serve_the_table(t_philo *philo)
{
	int		i;

	i = 0;
	while (++i <= philo->data->total_philos)
	{
		if (i == 1 || philo->process_id)
			philo->process_id = fork();
		if (!philo->process_id)
		{
			philo->id = i;
			break ;
		}
	}
	if (!philo->process_id)
	{
		if (ft_eat_alone(philo))
			exit(EXIT_SUCCESS);
	}
	else
		waitpid(0, NULL, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_data			*data;

	if (argc > 6 || argc < 5)
		return (EXIT_FAILURE);
	if (validate_arguments(argc - 1, &argv[1], &data)
		|| init_philo(data, &philo))
		return (EXIT_FAILURE);
	serve_the_table(philo);
	clear_philo(&philo);
	return (EXIT_SUCCESS);
}
