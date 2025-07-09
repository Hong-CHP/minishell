/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:52:39 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/09 19:41:27 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**set_charset(char **charset)
{
	charset = (char **)malloc(sizeof(char *) * 5);
	if (!charset)
		return (NULL);
	charset[0] = "<";
	charset[1] = "<<";
	charset[2] = ">>";
	charset[3] = ">";
	charset[4] = NULL;
	return (charset);
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

void    fill_args_zero_quote(char **cmds_split, char **charset, t_command *command)
{
    int	words;
    int j;
    
    words = count_utill_charset(cmds_split, charset);
	command->args = (char **)malloc(sizeof(char *) * (words + 1));
	if (!command->args)
		return ;
	j = 0;
	while (j < words)
	{
		command->args[j] = ft_strdup(cmds_split[j]);
		j++;
	}
	command->args[j] = NULL;
}

//doit essayer une command:
//cat -e '"hel'lo' world"' | grep hello > out.txt
//problem de confusion
char	**extract_cmd_args(char **cmds_split, char *content, t_command *command)
{
	char	**charset;
	//malloc need to be free then
	
	charset = set_charset(NULL);
	if (if_quote(content) == 0)
        fill_args_zero_quote(cmds_split, charset, command);
	else if (if_quote(content) > 0)
		fill_args_if_quote(content, cmds_split, command, charset);
    int i = 0;
    while (command->args[i])
    {
        printf("command->args is : %s\n", command->args[i]);
        i++;
    }
	free(charset);
	return (command->args);
}
