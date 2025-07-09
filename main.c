/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:48 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/09 19:25:18 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	minishell(char *input)
{
	t_cmdlist *head;
	
	if (*input == '\0')
		return ;
	head = NULL;
	head = create_cmds_list(head, input);
	if (!head)
		return ;
}

int	main(int argc, char **argv)
{
	char	*input;
	(void)	argv;
	
	if (argc != 1)
		return (1);
	input = readline("minishell>>");
	while (input)
	{
		if (*input)
		{
			add_history(input);
			minishell(input);
		}
		if (ft_strcmp(input, "clear") == 0)
			rl_clear_history(); 
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
		input = readline("minishell>>");
	}
	printf("exit\n");
	return (0);
}
