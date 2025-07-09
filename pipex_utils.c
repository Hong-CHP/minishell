/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:26:34 by hporta-c          #+#    #+#             */
/*   Updated: 2025/07/09 14:28:11 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int if_pipex(char *input)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(input[i])
    {
        if (input[i] == '|')
            count++;
        i++;
    }
    return (count);
}