/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:48:51 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/22 16:14:57 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		no_quote_no_space(char *str)
{
	int	i;

	i = 0;
	if (if_quote(str) == 0)
	{
		while (str[i])
		{
			if (str[i] == ' ')
				return (0);
			i++;
		}
	}
	return(1);
}

int	if_export_variable(char *content)
{
	if (ft_strncmp("export ", content, 7) == 0)
		return (1);
	return (0);
}


char	*if_variable_val(char *content)
{
	char	*val;
	int		count_val;
	int		i;

	i = 0;
	count_val = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (content[i])
		i++;
	if (!no_quote_no_space(&content[i]))
		return (NULL);
	while (content[i])
	{
		count_val++;
		i++;
	}
	if (count_val == 0 || content[i] == ' ')
		return (NULL);
	val = malloc(sizeof(char) * (count_val + 1));
	if (!val)
		return (NULL);
	ft_memset(val, 0, count_val + 1);
	return (val);
}

char	*if_variable_var(char *content)
{
	int		i;
	char	*var;
	int		count_var;

	i = 0;
	count_var = 0;
	while (content[i] && (content[i] >= 'A' && content[i] <= 'Z'))
	{
		count_var++;
		i++;
	}
	if (count_var == 0)
		return (NULL);
	if (content[i] && content[i] != '=')
		return (NULL);
	else if (content[i] && content[i] == '=')
		i++;
	var = malloc(sizeof(char) * (count_var + 1));
	if (!var)
		return (NULL);
	ft_memset(var, 0, count_var + 1);
	return (var);
}

int	check_input_var_val(char *input)
{
	int	i;

	i = 0;
	if (if_export_variable(input))
		i += 7;
	while (input[i] && input[i] != '=')
	{
		if (input[i] < 'A' || input[i] > 'Z')
			return (0);
		i++;
	}
	return (1);
}