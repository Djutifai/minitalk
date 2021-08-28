#include "../includes/minitalk.h"

int	ft_validatestr(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

int ft_check_everything(int argc, char *pid)
{
	if (argc != 3)
	{
		write(1, "Check arguments!\nRight usage ./client pid message\n", 50);
		return (-1);
	}
	if (ft_validatestr(pid) == -1)
	{
		write(1, "Invalid PID\n", 12);
		return (-1);
	}
	return (1);
}

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
