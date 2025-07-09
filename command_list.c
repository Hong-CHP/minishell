/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:21:08 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/09 19:34:10 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	clean_cmdlist(t_cmdlist **head)
{
	t_cmdlist	*cur;
	t_cmdlist	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->command);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

t_cmdlist    *fill_cmd_node_content(t_cmdlist *cmd_node, char *single_cmd)
{
	if (!single_cmd)
		return (NULL);
	cmd_node->command = (t_command *)malloc(sizeof(t_command));
	if (!cmd_node->command)
	{
		free(cmd_node);
		return (NULL);
	}
	ft_memset(cmd_node->command, 0, sizeof(t_command));
	cmd_node->command = tokenize_cmd(cmd_node->command, single_cmd);
	if (!cmd_node->command)
	{
		free(cmd_node->command);
		return (NULL);
	}
	return (cmd_node);
}

t_cmdlist	*new_cmd_node(char *single_cmd)
{
	t_cmdlist	*cmd_node;
	
	cmd_node = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!cmd_node)
		return (NULL);
	fill_cmd_node_content(cmd_node, single_cmd);
	if (!cmd_node)
		return (NULL);
	cmd_node->next = NULL;
	return (cmd_node);
}

void	add_cmdlist_back(t_cmdlist **head, t_cmdlist *cmd_node)
{
	t_cmdlist	*cur;

	cur = NULL;
	if (!*head)
		*head = cmd_node;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = cmd_node;
	}
}

t_cmdlist	*create_cmds_list(t_cmdlist *head, char *input)
{
	// t_cmdlist	*head;
	t_cmdlist	*cmd_node;
	char	**cmds_pipex;
	//malloc split need to be free then
	int	i;

	// head = NULL;
	cmds_pipex = ft_split(input, '|');
	if (!cmds_pipex)
		return (NULL);
	i = 0;
	while (cmds_pipex[i])
	{
		cmd_node = new_cmd_node(cmds_pipex[i]);
		if (!cmd_node)
		{
			clean_cmdlist(&head);
			free_split(cmds_pipex);
			return (NULL);
		}
		add_cmdlist_back(&head, cmd_node);
		i++;
	}
	free_split(cmds_pipex);
	return (head);
}
