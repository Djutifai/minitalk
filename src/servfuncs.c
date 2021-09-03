#include "../includes/minitalk.h"

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
