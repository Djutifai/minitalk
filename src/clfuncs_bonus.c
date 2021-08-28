#include "../includes/minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	ssize_t	res;
	int		digits;

	digits = 0;
	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + ((char)str[i] - '0');
		i++;
		digits++;
	}
	return ((int)res);
}
