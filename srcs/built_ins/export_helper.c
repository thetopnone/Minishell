/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:25:21 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/28 18:25:22 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//A function that handles export error
int	ft_export_error(t_shell *shell)
{
	shell->err->ft_export = 1;
	return (shell->last_exit = 1);
}

//Helper for reassigning the envar values
int	ft_reassign_value(t_envar *envar, char *value)
{
	if (value != NULL)
	{
		free(envar->value);
		envar->value = value;
	}
	envar->is_exported = 1;
	return (0);
}
