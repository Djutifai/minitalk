#include "minitalk.h"

void	ft_get_len(int signum, pid_t client_pid, int *len)
{
	static int		counter;

	if (!counter)
		counter = 1 << 30;
	if (signum == SIGUSR1)
		*len = *len | counter;
	counter >>= 1;
	ft_send_signal(client_pid, SIGUSR1);
}

void	ft_putnbr(int n)
{
	char	divdigit;

	if (n >= 10)
	{
		divdigit = (n % 10) + 48;
		n = n / 10;
		ft_putnbr(n);
		write(1, &divdigit, 1);
	}
	else if (n >= 0 && n <= 9)
	{
		divdigit = n + 48;
		write(1, &divdigit, 1);
	}
}

int	ft_if_not_str(int *index, char **str, pid_t client_pid, int len)
{
	*index = 0;
	*str = ft_calloc(len, sizeof(**str));
	if (!*str)
	{
		ft_send_signal(client_pid, SIGUSR2);
		return (-1);
	}
	return (1);
}

void	ft_write_and_free(char **str)
{
	int	i;

	i = ft_strlen(*str);
	write(1, *str, i);
	free(*str);
	*str = NULL;
	ft_write_str("\nServer is ready for the next client\nPid is: ");
	ft_putnbr(getpid());
	write(1, "\n", 1);
}
