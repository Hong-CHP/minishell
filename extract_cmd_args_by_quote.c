/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_args_by_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:20:20 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 16:46:24 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*find_words_in_quote(char *content, char ch)
{
	int		i;
	int		start;
    size_t  len;
	char	*str;
	//malloc need to be free then
	
    len = ft_strlen(content);
	i = 0;
	str = NULL;
	start = 0;
	while (i < (int)len && content[i] != ch)
		i++;
	if (content[i] == '\0')
		return (NULL);
	i++;
	start = i;
	while (i < (int)len && content[i] != ch)
		i++;
	if(content[i] == '\0')
		return (NULL);
	str = malloc(sizeof(char) * (i - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &(content[start]), i - start + 1);
	return (str);
}

char	*dup_str_without_quote(char *str, char ch)
{
	char	*word;
	int	i;
	int	j;

	j = 0;
	i = 0;
	word = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!word)
		return (NULL);
	while (str[i])
	{
		if (str[i] != ch)
		{
			word[j] = str[i];
			j++;
		}
		i++;
	}
	word[j] = '\0';
	return (word);
}

int	find_dollar_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

void	fill_args(char **split, t_cmdlist *cmd_node, char **set)
{
	int	nb_wd;
	int	i;
	char ch;
	int	j;
	int	k;
	char	*word;
	//malloc need be free
	char	*res;
	//malloc need be free

	printf("5.head var ptr is %p\n", cmd_node->var_list);
	nb_wd = count_utill_charset(split, set);
	cmd_node->command->args = (char **)malloc(sizeof(char *) * (nb_wd + 1));
	if (!cmd_node->command->args)
		return ;
	i = 0;
	j = 0;
	k = 0;
	res = ft_strdup("");
	while (split[i] && i < nb_wd)
	{
		if (if_quote(split[i]) != 0)
		{
			ch = if_quote(split[i]);
			if ((split[i][0] == '\'' || split[i][0] == '\"')
				&& (split[i][0] == split[i][ft_strlen(split[i]) - 1]))
				{
					if (ch == '\"' && if_dollar_sign(split[i]) != 0)
						word = reg_dollar(split[i], cmd_node);
					cmd_node->command->args[k] = find_words_in_quote(split[i], ch);
					k++;
				}
			else if ((split[i][0] == '\'' || split[i][0] == '\"')
				&& (split[i][0] != split[i][ft_strlen(split[i]) - 1]))
				{
					j = i;
					while (split[j] && split[j][ft_strlen(split[j]) - 1] != ch)
					{
						if (split[j][0] == ch)
							word = supp_quote_add_space(split[j]);
						else
						{
							word = ft_strdup(split[j]);
							word = ft_strjoin(word, " ");
						}
						if (ch == '\"' && if_dollar_sign(word) != 0)
						{
							word = reg_dollar(word, cmd_node);
							word = ft_strjoin(word, " ");
						}
						res = ft_strjoin(res, word);
						printf("the word is: %s, the res is %s\n", word, res);
						free(word);
						j++;
					}
					if (split[j])
					{
						printf("hehe, here is last quote word\n");
						word = supp_last_quote(split[j]);
						printf("last quote word is %s\n", word);
						if (ch == '\"' && if_dollar_sign(word) != 0)
							word = reg_dollar(word, cmd_node);
						res = ft_strjoin(res, word);
						cmd_node->command->args[k] = res;
						printf("the word is: %s, the res is %s\n", word, res);
						free(word);
						k++;
					}
					i = j;
				}
			else
			{
				cmd_node->command->args[k] = dup_str_without_quote(split[i], ch);
				k++;
			}
		}
		else
		{
			cmd_node->command->args[k] = ft_strdup(split[i]);
			k++;
		}
		i++;
	}
	cmd_node->command->args[k] = NULL;
	i = 0;
	while (cmd_node->command->args[i])
		printf("args is %s\n", cmd_node->command->args[i++]);
}
