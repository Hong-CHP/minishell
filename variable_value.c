/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:54:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 17:14:30 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	return (value);
}

void	registre_var_val(char *content, t_variable *local_v, char *value)
{
	//local_v->var nned free
	//local_v->val nned free
	if (local_v->exported == 1)
		local_v->var = if_variable_var(&content[7]);
	else
		local_v->var = if_variable_var(content);
	local_v->val = if_variable_val(content);
	if (!local_v->var)
		return ;
	if (!local_v->val)
	{
		free(local_v->var);
		return ;
	}
	if (local_v->exported == 1)
		fill_variable_value(&content[7], local_v->var, local_v->val);
	else
		fill_variable_value(content, local_v->var, local_v->val);
	if (if_quote(local_v->val) != 0)
	{
		value = extract_value(local_v->var, local_v->val);
		free(local_v->val);
		local_v->val = value;
	}
}

void 	init_registre_variable(t_variable *v_content, char *content)
{
	char		*value;

	value = NULL;
	if (if_export_variable(content))
	{
		v_content->exported = 1;
	}
	registre_var_val(content, v_content, value);
	free(value);
}
