/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:52:39 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 13:56:12 by hporta-c         ###   ########.fr       */
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

char	**extract_cmd_args(char **cmds_split, char *content, t_cmdlist *cmd_node)
{
	(void)	content;
	char	**charset;
	//malloc need to be free then
	
		printf("4.head var ptr is %p\n", cmd_node->var_list);
	charset = set_charset(NULL);
	fill_args(cmds_split, cmd_node, charset);
    int i = 0;
    while (cmd_node->command->args[i])
    {
        printf("cmd_node->command->args is : %s\n", cmd_node->command->args[i]);
        i++;
    }
	free(charset);
	return (cmd_node->command->args);
}
