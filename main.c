/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:48 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:48 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	minishell(char *input, t_varlist **head_var)
{
	t_cmdlist	*head_cmd;
	t_variable *var_node;

	if (*input == '\0')
		return ;
	head_cmd = NULL;
	var_node = NULL;
	if (head_var)
	{
		t_varlist *cur = *head_var;
		while(cur)
		{
			printf("cur content: %s = %s\n", cur->var_data->var, cur->var_data->val);
			cur = cur->next;
		}
	}
	if (if_equal(input) || if_export_variable(input))
		create_var_list_or_find_node(head_var, input, var_node);
	else
	{
		printf("0.head var ptr is %p\n", head_var);
		head_cmd = create_cmds_list(head_cmd, input, head_var);
		if (!head_cmd)
			return ;
	}
}

int	main(int argc, char **argv)
{
	char	*input;
	t_varlist	*head_var;
	(void)	argv;
	
	if (argc != 1)
		return (1);
	head_var = NULL;
	input = readline("\1\033[1;33m\2minishell\1\033[0m\2>");
	while (input)
	{
		if (ft_strcmp(input, "clear") == 0)
			rl_clear_history(); 
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			minishell(input, &head_var);
		}
		free(input);
		input = readline("\1\033[1;33m\2minishell\1\033[0m\2>");
	}
	clean_var_list(&head_var);
	printf("exit\n");
	return (0);
}
