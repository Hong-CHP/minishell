/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:21:34 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/15 17:04:07 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_command	*tokenize_cmd(t_command *command, char *content)
{
	char		**cmds_split;
	//malloc split need to be free then
	int			i;

	printf("---------------------\n");
	printf("content of command is : %s\n", content);
	cmds_split = ft_split(content, ' ');
	i = 0;
	while (cmds_split[i])
	{
		printf("cmds_splits = %s\n", cmds_split[i]);
		i++;
	}
	command->cmd = cmds_split[0];
	command->args = extract_cmd_args(cmds_split, content, command);
	if (!command->args)
	{
		free(command->cmd);
		free_split(cmds_split);
		return (NULL);
	}
	// fill_s_command(cmds, cmds_split, input);
	free_split(cmds_split);
	return (command);
}
