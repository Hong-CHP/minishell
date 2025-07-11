/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:52:39 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/11 15:32:42 by hporta-c         ###   ########.fr       */
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

char	**extract_cmd_args(char **cmds_split, char *content, t_command *command)
{
	(void)content;
	char	**charset;
	//malloc need to be free then
	
	charset = set_charset(NULL);
	fill_args(cmds_split, command, charset);
    int i = 0;
    while (command->args[i])
    {
        printf("command->args is : %s\n", command->args[i]);
        i++;
    }
	free(charset);
	return (command->args);
}
