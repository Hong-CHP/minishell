/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:33:50 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/11 15:43:00 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		if_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return ((int)'\'');
		else if (str[i] == '\"')
			return ((int)'\"');
		i++;
	}
	return (0);
}

char *supp_quote_add_space(char *str)
{
	char *word;
	int	i;
	int	j;
	
	word = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!word)
		return (NULL);
	i = 1;
	j = 0;
	while (i < (int)ft_strlen(str))
	{
		word[j] = str[i];
		j++; 
		i++;
	}
	word[j] = ' ';
	word[i] = '\0';
	return (word);
}

char *supp_last_quote(char *str)
{
	char *word;
	int	i;
	int	j;
	
	j = 0;
	i = 0;
	word = malloc(sizeof(char) * ft_strlen(str));
	if (!word)
		return (NULL);
	while (i < ((int)ft_strlen(str) - 1))
	{
		word[j] = str[i];
		j++; 
		i++;
	}
	word[j] = '\0';
	return (word);
}

int     count_utill_charset(char **cmds_split, char **charset)
{
    int	i;
	int	j;
    
    i = 0;
	j = 0;
	while(cmds_split[i])
	{
		j = 0;
		while (charset[j])
		{
			if (ft_strcmp(cmds_split[i], charset[j]) == 0)
				return (i) ;
			j++;
		}
		i++;
	}
    return (i);
}