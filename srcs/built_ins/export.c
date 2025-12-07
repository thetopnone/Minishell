/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:30:31 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Free array used for printing alphabetically sorted array
void	ft_free_tmp_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_print_sorted_env_arr(char **arr)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (arr[i])
	{
		temp = ft_strjoin("declare -x ", arr[i++]);
		ft_putendl_fd(temp, 1);
		free(temp);
	}
}

//Print alphabetically sorted environmental array
char	**ft_sort_env_arr(char **arr)
{
	char	*temp;
	int		i;
	int		j;

	if (!arr || !*arr)
		return (NULL);
	i = 0;
	while (arr[i + 1])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

//Handling export with no argument
void	ft_export_with_no_arg(t_shell *shell)
{
	char	**env_var_arr;
	int		i;

	env_var_arr = malloc(sizeof(char *) * (shell->env_amount + 1));
	i = 0;
	while (shell->envp[i])
	{
		env_var_arr[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	env_var_arr[i] = NULL;
	ft_print_sorted_env_arr(ft_sort_env_arr(env_var_arr));
	ft_freearr(env_var_arr, i);
}

//Check if passes key exists, if not, check if it has valid chars for env
//variable name, then create the envar with the passed key
int	ft_export(char **argv, t_shell *shell)
{
	char	*key;
	char	*value;
	size_t	env_amount;
	t_envar	*envar;

	if (!argv || (argv[1] && argv[2]))
		ft_export_error(shell);
	if (!argv[1])
		ft_export_with_no_arg(shell);
	key = ft_extract_key(argv[1], shell->err);
	value = ft_extract_value(argv[1], shell->err);
	env_amount = ft_envar_amount(shell->envc, shell->err);
	envar = ft_get_envar(shell->envc, key, shell->err);
	if (key == NULL || ft_valid_env(key, shell->err) == 1)
		ft_export_error(shell);
	if (envar == NULL)
		ft_add_envar(&(shell->envc), ft_new_envar(key, value, 1, shell->err),
			shell->err);
	else
		ft_reassign_value(envar, value);
	ft_freearr(shell->envp, env_amount);
	shell->envp = ft_set_envp(shell->envc, shell->err);
	shell->env_amount = ft_envar_amount(shell->envc, shell->err);
	return (shell->last_exit = 0);
}
