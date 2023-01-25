/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:42:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/02 20:08:36 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	ft_atoi(const char *num)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while ((num[i] > 8 && num[i] < 14) || num[i] == 32)
		i++;
	if (num[i] == 43 || num[i] == 45)
	{
		if (num[i] == 45)
			sign = -1;
		i++;
	}
	while (num[i] > 47 && num[i] < 58)
	{
		result = result * 10 + num[i] - 48;
		i++;
	}
	return (result * sign);
}

long long	ft_get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

void	ft_say(const char *expression, t_philo *philo)
{
	sem_wait(philo->data->filedes_sem);
	printf(expression, ft_get_time(), philo->id);
	sem_post(philo->data->filedes_sem);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

void	ft_usleep(long long time)
{
	long long	i;

	i = ft_get_time();
	while (ft_get_time() - i < time)
		usleep(10);
}
