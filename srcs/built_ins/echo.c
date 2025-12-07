/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:32:29 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Flag can only be in second spot in echo
static bool	ft_check_for_nflag(char *argv)
{
	if (ft_strncmp(argv, "-n", 3) == 0)
		return (true);
	return (false);
}

//syntax will be checked earlier (before calling the echo function)
//No need for file descriptor usage, redirections and pipes will be replugging
//the stdin and stdout anyways. Pay attention that echo does not take input
//from stdin, just puts the string passed to the stdout (again, redirections
//and pipes are replugging it)
int	ft_echo(char **argv, t_shell *shell, t_error *err)
{
	int		i;

	if (!argv || !argv[0])
	{
		err->echo = 1;
		return (shell->last_exit = 1);
	}
	i = 1;
	if (!argv[1])
		write(STDOUT_FILENO, "\n", 1);
	if (argv[1] && ft_check_for_nflag(argv[1]) == 1)
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (argv[1] && ft_check_for_nflag(argv[1]) == 0)
		write(STDOUT_FILENO, "\n", 1);
	err->echo = 0;
	return (shell->last_exit = 0);
}
