/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:30:07 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 14:59:41 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_vars_vals(char **vars, char **vals)
{
	int i;

	i = 0;
	while (vars[i])
	{
		free(vars[i]);
		if (vals[i])
			free(vals[i]);
		i++;
	}
	free(vars);
	vars = NULL;
	free(vals);
	vals = NULL;
}

int if_dollar_sign(char *str)
{
	int i;
	int count;
		
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	real_length_of_word(char *str, int vals_len)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] == '$')
		{
			i++;
			while(str[i] >= 'A' && str[i] <= 'Z')
				i++;
		}
		else
		{
			printf("str[i] is %c and len is %d\n", str[i], len);
			len++;
			i++;
		}
	}
	len--;
	len = len + vals_len;
	return (len);
}