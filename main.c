/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:48 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/07 19:30:08 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	char	*input;
	size_t	len;
	(void)	argv;

	if (argc != 1)
		return (1);
	input = readline("minishell>>");
	while (input)
	{
		len = ft_strlen(input);
		if (*input)
			add_history(input);
		if (ft_strncmp(input, "clear", len) == 0)
			rl_clear_history(); 
		if (ft_strncmp(input, "exit", len) == 0)
		{
			free(input);
			break ;
		}
		free(input);
		input = readline("minishell>>");
	}
	free(input);
	return (0);
}