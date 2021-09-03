#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_validate_pid(const char *str);
int		ft_check_everything(int argc, char *pid); 
int		ft_atoi(char const *str);
void	ft_putnbr(int nb);
void	ft_get_len(int signum, pid_t server_pid, int *len);
int		ft_strlen(const char *str);
void	ft_send_len(pid_t server_pid, int len);
void	ft_send_signal(pid_t pid, int signum);
void	ft_write_str(char *str);

#endif
