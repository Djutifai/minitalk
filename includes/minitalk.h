#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_validatestr(const char *str);
int		ft_check_everything(int argc, char *pid); 
int		ft_atoi(char const *str);
void	ft_putnbr(int nb);

#endif
