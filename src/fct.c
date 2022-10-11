#include "../include/philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


int	ft_atoi(const char *str)
{
	int		negative;
	long	nb;

	negative = 1;
	nb = 0;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - 48;
		str++;
		if (nb * negative > 2147483647)
			return (-1);
		if (nb * negative < -2147483648)
			return (0);
	}
	return (nb * negative);
}

void init_arg(t_arg *arg, char **s)
{
	arg->start_time = get_time_in_ms();
	arg->nbr_of_philo = ft_atoi(s[1]);
	arg->t = 1;
	arg->time_to_die = ft_atoi(s[2]);
	arg->time_to_eat = ft_atoi(s[3]);
	arg->time_to_sleep = ft_atoi(s[4]);
	if(s[5])
		arg->nmbr_of_time_philo_must_eat = ft_atoi(s[5]);
	else
		arg->nmbr_of_time_philo_must_eat = 0;
}


 int get_random (int max)
{
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}
