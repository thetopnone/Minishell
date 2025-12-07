/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 21:20:00 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_received_signal = 0;

int	ft_check_input(char *input)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(input) - 1;
	if (!input)
		return (1);
	while (input[start] && input[start] == ' ')
		start++;
	while (end > 0 && input[end] == ' ')
		end--;
	if (input[start] == '|' || input[end] == '|')
	{
		perror("Error: INVALID SYNTAX\n");
		return (1);
	}
	return (0);
}

void	ft_main_initialization(t_shell **shell, char **envp)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->err = ft_calloc(1, sizeof(t_error));
	(*shell)->envc = ft_set_envc(envp, (*shell)->err);
	(*shell)->env_amount = ft_envar_amount((*shell)->envc, (*shell)->err);
	(*shell)->envp = ft_set_envp((*shell)->envc, (*shell)->err);
}

void	ft_loop_functionality(t_shell **shell)
{
	(*shell)->chain = lexer((*shell)->input, (*shell)->err);
	(*shell)->pipeline = ft_parser(&((*shell)->chain), (*shell)->err);
	ft_expander((*shell)->pipeline, *shell, (*shell)->err);
	if (!ft_error_check_parser((*shell)->err))
		ft_executor((*shell)->pipeline, *shell, (*shell)->err);
	ft_del_pipeline(&(*shell)->pipeline, (*shell)->err);
	ft_bzero((*shell)->err, sizeof(t_error));
	free((*shell)->input);
	ft_refresh_rl();
}

int	main(int argc, char	*argv[], char **envp)
{
	t_shell	*shell;

	if (argc == 1 && argv)
	{
		ft_main_initialization(&shell, envp);
		while (1)
		{
			ft_signals(SIGINT, 0);
			ft_signals(SIGQUIT, 0);
			shell->input = readline("minishell$> ");
			if (shell->input && *(shell->input))
				add_history(shell->input);
			else if (!shell->input)
				ft_exit(NULL, shell->pipeline, shell);
			else
			{
				ft_refresh_rl();
				continue ;
			}
			if (ft_check_input(shell->input) == 0)
				ft_loop_functionality(&shell);
		}
	}
	return (0);
}
