/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:54:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/14 17:02:11 by hporta-c         ###   ########.fr       */
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

void	fill_variable_value(char *content, char *var, char *val)
{
	int	i;
	int	j;

	i = 0;
	while (content[i] && (content[i] >= 'A' && content[i] <= 'Z'))
	{
		var[i] = content[i];
		i++;
	}
	if (content[i] && content[i] == '=')
		i++;
	j = 0;
	while (content[i])
	{
		val[j] = content[i];
		j++;
		i++;
	}
	val[j] = '\0';
}

char	*extract_value(char *var, char *val)
{
	char	*value;
	int		ch;

	if (if_quote(val) != 0 && val[0] != val[ft_strlen(val) - 1])
	{
		free(var);
		free(val);
		return (NULL);
	}
	ch = if_quote(val);
	value = find_words_in_quote(val, ch);
	printf("value is %s\n", value);
	return (value);
}

void	registre_var_val(char *content, t_localvar *local_v, char *value)
{
	//local_v->var nned free
	//local_v->val nned free

	local_v->var = if_variable_var(content);
	local_v->val = if_variable_val(content);
	if (!local_v->var)
		return ;
	if (!local_v->val)
	{
		free(local_v->var);
		return ;
	}
	fill_variable_value(content, local_v->var, local_v->val);
	printf("orgine : val = var: %s=%s\n", local_v->var, local_v->val);
	if (if_quote(local_v->val) != 0)
	{
		value = extract_value(local_v->var, local_v->val);
		free(local_v->val);
		local_v->val = value;
		printf("new one : val = var: %s=%s\n", local_v->var, local_v->val);
	}
	printf("------------\n");
}

t_localvar 	*init_registre_variable(char *content)
{
	t_localvar	*local_v;
	char		*value;

	local_v = malloc(sizeof(t_localvar));
	if (!local_v)
		return (NULL);
	ft_memset(local_v, 0, sizeof(local_v));
	value = NULL;
	registre_var_val(content, local_v, value);
	free(value);
	printf("local_var si %s and local_val is %s\n", local_v->var, local_v->val);
	return (local_v);
}
