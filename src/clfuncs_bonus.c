#include "../includes/minitalk.h"

void	ft_send_len(pid_t server_pid, int len)
{
	static int		myLen;
	static int		counter;
	static pid_t	myPid;

	if (!myLen)
	{
		myLen = len;
		counter = 1 << 30;
		myPid = server_pid;
	}
	if (counter)
	{
		if (counter & myLen)
			ft_send_signal(myPid, SIGUSR1);
		else
			ft_send_signal(myPid, SIGUSR2);
		counter >>= 1;
		usleep(30);
	}
}

int	ft_validate_pid(const char *str)
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

int	ft_check_everything(int argc, char *pid)
{
	if (argc != 3)
	{
		ft_write_str("Check arguments!\nRight usage ./client pid message\n");
		return (-1);
	}
	if (ft_validate_pid(pid) == -1)
	{
		ft_write_str("Invalid PID\n");
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
