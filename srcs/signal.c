/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:07:56 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/26 17:13:23 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sa_handler_1(int signal)
{
	g_received_signal = signal;
	if (signal == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sa_handler_2(int signal)
{
	g_received_signal = signal;
	if (signal == SIGINT)
		write (1, "\n", 1);
}

//mode 0 only in parent
//mode 1 only in child
//mode 2 only in parent while child is running
void	ft_signals(int signal, int mode)
{
	struct sigaction	sa_parent;

	sigemptyset(&sa_parent.sa_mask);
	if (signal == SIGQUIT)
	{
		if (mode == 1)
			sa_parent.sa_handler = SIG_DFL;
		else
			sa_parent.sa_handler = SIG_IGN;
	}
	else if (signal == SIGINT)
	{
		if (mode == 2)
			sa_parent.sa_handler = ft_sa_handler_2;
		else if (mode == 1)
			sa_parent.sa_handler = SIG_DFL;
		else
			sa_parent.sa_handler = ft_sa_handler_1;
	}
	sa_parent.sa_flags = SA_RESTART;
	if (sigaction(signal, &sa_parent, NULL))
		exit(2);
}
