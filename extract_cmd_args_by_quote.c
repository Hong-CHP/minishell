/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_args_by_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:20:20 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/09 19:17:36 by hporta-c         ###   ########.fr       */
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

void	find_start_end_idx_quote(int *s_i, int *e_i, char **cmds_split, char ch)
{
	int	i;
	int	j;
	
	i = 0;
	*s_i = -1;
	*e_i = -1;
	while (cmds_split[i][0] != ch)
		i++;
	if (cmds_split[i][0] == ch)
		*s_i = i;
	while (cmds_split[i])
	{
		j = 0;
		while (cmds_split[i][j])
		{
			if (cmds_split[i][j] == ch)
				*e_i = i;
			j++;
		}
		i++;
	}
}

char    *find_words_and_idx(char *content, int *s_idx, int *e_idx, char **cmds_split)
{
    char        ch;
	char		*words;
	//malloc in func find_sngle_quote, need to be free then

	if (if_quote(content) == 1)
        ch = '\'';
    else if (if_quote(content) == 2)
        ch = '\"';
    words = find_words_in_quote(content, ch);
    find_start_end_idx_quote(s_idx, e_idx, cmds_split, ch);
    return (words);
}

void    fill_args(t_command *cmd, char **split, char *content, int nb_wd)
{
    int     i;
    int     j;
    int     s_idx;
	int     e_idx;
    char    *words;
    //malloc in func find_sngle_quote, need to be free then

    words = find_words_and_idx(content, &s_idx, &e_idx, split);
    i = 0;
    j = 0;
    while (split[i] && i < nb_wd)
    {
        if (i == s_idx)
        {
            cmd->args[j] = ft_strdup(words);
            i = e_idx + 1;
        }
        else
            cmd->args[j] = ft_strdup(split[i]);
        i++;
        j++;
    }
    cmd->args[j] = NULL;
    free(words);
}

void    fill_args_if_quote(char *cnt, char **split, t_command *cmd, char **set)
{
    int         s_idx;
	int         e_idx;
    int         nb_wd;

    find_words_and_idx(cnt, &s_idx, &e_idx, split);
    nb_wd = count_utill_charset(split, set);
    nb_wd -= (e_idx - s_idx);
    cmd->args = (char **)malloc(sizeof(char *) * (nb_wd + 1));
	if (!cmd->args)
		return ;
    fill_args(cmd, split, cnt, nb_wd);
}
