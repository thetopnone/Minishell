/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:55:51 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 20:48:49 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_inquote(char *s, int *s_quote, int *d_quote, size_t *words)
{
	char	c;

	c = *s;
	if (c == '\'')
	{
		if (*s_quote)
			*s_quote = 0;
		else
		{
			*s_quote = 1;
			(*words)++;
		}
	}
	else if (c == '"')
	{
		if (*d_quote)
			*d_quote = 0;
		else
		{
			*d_quote = 1;
			(*words)++;
		}
	}
	else
		return ;
}

//in_arr[0] = in_word, in_arr[1] = in_squote, in_arr[2] = in_dquote
void	ft_wa_handle_word(int in_arr[], size_t *words, char *s)
{
	in_arr[0] = 1;
	(*words)++;
	if (!in_arr[1] && *s == '"')
		ft_inquote(s, &in_arr[1], &in_arr[2], words);
	else if (!in_arr[2] && *s == '\'')
		ft_inquote(s, &in_arr[1], &in_arr[2], words);
}

int	ft_wa_pipe(char **s, size_t *words)
{
	if (!s || !*s)
		return (1);
	if (!**s)
		return (1);
	if (*(*s - 1) != ' ' || *(*s + 1) != ' ')
	{
		if (*(*s - 1) && *(*s - 1) != ' ')
			(*words)++;
		if (*(*s + 1) && *(*s + 1) != ' ')
			(*words)++;
	}
	else
		(*words)++;
	return (0);
}

void	ft_wa_init(size_t *words, int in_arr[3])
{
	*words = 0;
	in_arr[0] = 0;
	in_arr[1] = 0;
	in_arr[2] = 0;
}
