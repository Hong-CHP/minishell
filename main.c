/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:48 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/15 18:10:38 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	minishell(char *input, t_varlist **head_var)
{
	t_cmdlist	*head_cmd;
	
	if (*input == '\0')
		return ;
	head_cmd = NULL;
	if (if_equal(input))
		create_var_list(head_var, input);
	else
	{		
		head_cmd = create_cmds_list(head_cmd, input);
		if (!head_cmd)
			return ;
	}
	clean_cmdlist(&head_cmd);
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
