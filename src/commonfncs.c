#include "../includes/minitalk.h"

int ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_write_str(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_send_signal(pid_t pid, int signum)
{
	if (kill(pid, signum) == -1)
		ft_write_str("Error in sending signals!\n");
}

