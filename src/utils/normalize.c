/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernede <mbernede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:21:32 by mbernede          #+#    #+#             */
/*   Updated: 2024/02/07 13:21:33 by mbernede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_string(char **input, int n)
{
	int		len;
	char	*result;
	int		i;

	len = ft_strlen(*input);
	if (len == n)
		return (OK);
	result = (char *)malloc((n + 1) * sizeof(char));
	if (len > n)
		ft_strlcpy(result, *input, n + 1);
	else
	{
		ft_strlcpy(result, *input, len + 1);
		i = len;
		while (i < n)
		{
			result[i] = ' ';
			++i;
		}
		result[n] = '\0';
	}
	free(*input);
	*input = ft_strdup(result);
	return (OK);
}

void	normalize_map(t_param *p)
{
	t_node	*tmp;

	tmp = p->tmp_map;
	while (tmp)
	{
		process_string(&(tmp->line), p->map.length);
		tmp = tmp->next;
	}
}
