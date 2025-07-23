/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:21:34 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 13:56:04 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_command	*tokenize_cmd(t_cmdlist *cmd_node, char *content)
{
	char		**cmds_split;
	//malloc split need to be free then
	int			i;

	printf("---------------------\n");
	printf("content of command is : %s\n", content);
	printf("3.head var ptr is %p\n", cmd_node->var_list);
	cmd_node->command = (t_command *)malloc(sizeof(t_command));
	if (!cmd_node->command)
	{
		free(cmd_node);
		return (NULL);
	}
	ft_memset(cmd_node->command, 0, sizeof(t_command));
	cmds_split = ft_split(content, ' ');
	i = 0;
	while (cmds_split[i])
	{
		printf("cmds_splits = %s\n", cmds_split[i]);
		i++;
	}
	cmd_node->command->cmd = cmds_split[0];
	cmd_node->command->args = extract_cmd_args(cmds_split, content, cmd_node);
	if (!cmd_node->command->args)
	{
		free(cmd_node->command->cmd);
		free_split(cmds_split);
		return (NULL);
	}
	// fill_s_cmd_node->command(cmds, cmds_split, input);
	free_split(cmds_split);
	return (cmd_node->command);
}
