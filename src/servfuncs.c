#include "../includes/minitalk.h"

void	ft_get_len(int signum, pid_t client_pid, int *len)
{
	static int counter;

	if (!counter)
		counter = 1 << 7;
	if (counter)
		if (signum == SIGUSR1)
			*len = *len | counter;
	counter >>= 1;
	if (kill(client_pid, SIGUSR1) == -1)
		write(1, "Error in sending signals!\n", 26);
	usleep(20);
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
