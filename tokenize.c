/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:21:34 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/14 16:19:30 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// t_command	*fill_s_command(t_command *cmds, char **cmds_split, char *input)
// {
// 	int	i;
// 	cmds->cmd = cmds_split[0];
// 	i = 1;
// 	while (cmds_split[i])
// 	{
// 		printf("cmds is %s\n", cmds_split[i]);
// 		if (cmds_split[i][0] == '\'' || cmds_split[i][0] == '\"')
// 			fill_args_by_quote(input, cmds_split, cmds);
// 		if (ft_strcmp(cmds_split[i], "<<") == 0)
// 			cmds->here_doc = 1;
// 		if (ft_strcmp(cmds_split[i], "<") == 0 && cmds_split[i + 1])
// 			cmds->infile = cmds_split[i + 1];
// 		if (ft_strcmp(cmds_split[i], "|") == 0)
// 			fill_next_cmd();
// 		if (ft_strcmp(cmds_split[i], ">") == 0 && cmds_split[i + 1])
// 			cmds->outfile = cmds_split[i + 1];
// 		if (ft_strcmp(cmds_split[i], ">>") == 0 && cmds_split[i + 1])
// 		{
// 			cmds->append = 1;
// 			cmds->outfile = cmds_split[i + 1];
// 		}
// 		i++;
// 	}
// 	return (cmds);
// }

t_command	*tokenize_cmd(t_command *command, char *content)
{
	char		**cmds_split;
	//malloc split need to be free then
	int			i;

	printf("---------------------\n");
	printf("content of command is : %s\n", content);
	if (if_equal(content))
		init_registre_variable(content);
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
